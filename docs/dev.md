# Tickstream - Technical Specification

## 1. Overview

**Tickstream** is a C++20 header-only library for generating pseudo real-time financial market tick data simulations. The library provides configurable random processes, realistic market microstructure, and a high-performance producer-consumer architecture suitable for algorithmic trading strategy development, backtesting, and system load testing.

## 2. Core Design Principles

- **Header-only**: Zero dependencies beyond C++20 standard library
- **Performance-first**: Sub-microsecond tick generation, lock-free where possible
- **Deterministic**: Seed-controlled reproducibility
- **Modular**: Pluggable processes, schedulers, and consumers
- **Real-time ready**: Suitable for both simulation and live integration

## 3. Architecture

```
┌─────────────────────────────────────────────────┐
│                   User Application              │
└─────────────────────────────────────────────────┘
                    │  subscribe() / poll()
                    ▼
┌─────────────────────────────────────────────────┐
│                  Stream Manager                 │
│  • Multi-stream coordination                   │
│  • Time synchronization                        │
│  • Correlation control                         │
└─────────────────────────────────────────────────┘
                    │
    ┌───────────────┼───────────────┐
    ▼               ▼               ▼
┌─────────┐   ┌─────────┐   ┌─────────┐
│ Stream  │   │ Stream  │   │ Stream  │
│ (AAPL)  │   │ (GOOGL) │   │ (MSFT)  │
└─────────┘   └─────────┘   └─────────┘
    │               │               │
┌───┴───────┐   ┌───┴───────┐   ┌───┴───────┐
│ Producer  │   │ Producer  │   │ Producer  │
│ • Process │   │ • Process │   │ • Process │
│ • Sched   │   │ • Sched   │   │ • Sched   │
└───────────┘   └───────────┘   └───────────┘
                    │
                    ▼
           ┌─────────────────┐
           │   Ring Buffer   │
           │ (Lock-free SPSC)│
           └─────────────────┘
                    │
                    ▼
           ┌─────────────────┐
           │    Consumer     │
           │ (User callback) │
           └─────────────────┘
```

## 4. Core Components Specification

### 4.1 `tick.hpp` - Data Model

```cpp
namespace tickstream {

struct Timestamp {
    int64_t nanoseconds;  // Since epoch
    // Helpers: to_string(), operator<<, comparisons
};

enum class TickType : uint8_t {
    TRADE,
    BID,
    ASK,
    BID_ASK,  // Both updated
    UNKNOWN
};

struct Tick {
    Timestamp timestamp;
    std::string symbol;
    double price;
    double volume;
    TickType type;
    
    // For bid/ask
    double bid_price;
    double ask_price;
    int32_t bid_size;
    int32_t ask_size;
    
    // Sequence number for ordering
    uint64_t sequence;
    
    // Trade-specific
    std::optional<std::string> trade_id;
    std::optional<bool> is_eod;  // End-of-day marker
};

// OHLCV bar aggregation
struct Bar {
    Timestamp open_time;
    Timestamp close_time;
    double open;
    double high;
    double low;
    double close;
    double volume;
    uint32_t tick_count;
};
} // namespace tickstream
```

### 4.2 `ring_buffer.hpp` - Lock-free Circular Buffer

**Requirements:**
- Single Producer, Single Consumer (SPSC) design
- Cache-line aligned to avoid false sharing
- Configurable capacity (power of two for bitmask optimization)
- Exception-safe push/pop operations
- Optional busy-wait/yield strategies

**Interface:**
```cpp
template<typename T, size_t Capacity = 1024>
class RingBuffer {
public:
    // Returns false if buffer is full (non-blocking)
    bool try_push(const T& item);
    
    // Blocks until space available or timeout
    bool push(const T& item, 
              std::chrono::nanoseconds timeout = std::chrono::nanoseconds::max());
    
    // Returns false if buffer is empty (non-blocking)
    bool try_pop(T& item);
    
    // Blocks until item available or timeout
    bool pop(T& item,
             std::chrono::nanoseconds timeout = std::chrono::nanoseconds::max());
    
    size_t size() const noexcept;
    size_t capacity() const noexcept;
    bool empty() const noexcept;
    bool full() const noexcept;
};
```

### 4.3 `producer.hpp` - Tick Generation

**Process Interfaces:**
```cpp
namespace tickstream::process {

// Base interface for all stochastic processes
class IProcess {
public:
    virtual ~IProcess() = default;
    virtual double next(double dt, std::mt19937_64& rng) = 0;
    virtual void reset(double initial_value) = 0;
    virtual std::unique_ptr<IProcess> clone() const = 0;
};

// Geometric Brownian Motion (Black-Scholes)
class GBM : public IProcess {
public:
    struct Config {
        double initial_price = 100.0;
        double mu = 0.05;      // Annual drift
        double sigma = 0.2;    // Annual volatility
        double risk_free_rate = 0.02;
    };
    
    GBM(Config config);
    // ... implementation
};

// Ornstein-Uhlenbeck (Mean-reverting)
class OU : public IProcess {
public:
    struct Config {
        double initial_price = 100.0;
        double mean = 100.0;   // Long-term mean
        double theta = 0.1;    // Mean reversion speed
        double sigma = 0.2;    // Volatility
    };
    // ... implementation
};

// Merton Jump Diffusion
class MertonJump : public IProcess {
public:
    struct Config {
        double initial_price = 100.0;
        double mu = 0.05;
        double sigma = 0.2;
        double jump_lambda = 0.1;  // Jump frequency
        double jump_mu = -0.02;    // Jump mean
        double jump_sigma = 0.05;  // Jump volatility
    };
    // ... implementation
};
} // namespace tickstream::process
```

**Scheduler Interfaces:**
```cpp
namespace tickstream::schedule {

class IScheduler {
public:
    virtual ~IScheduler() = default;
    virtual std::chrono::nanoseconds next_interval(std::mt19937_64& rng) = 0;
    virtual void reset() = 0;
};

// Poisson process (exponential intervals)
class Poisson : public IScheduler {
public:
    explicit Poisson(double lambda_per_second);  // λ = events per second
    // ... implementation
};

// Fixed interval
class FixedInterval : public IScheduler {
public:
    explicit FixedInterval(std::chrono::nanoseconds interval);
    // ... implementation
};

// Real-world trading calendar
class TradingCalendar : public IScheduler {
public:
    TradingCalendar(std::string exchange = "NYSE",
                    std::chrono::nanoseconds typical_interval = std::chrono::milliseconds(100));
    // ... implementation with market hours, holidays
};
} // namespace tickstream::schedule
```

**Microstructure Model:**
```cpp
namespace tickstream::microstructure {

class IMicrostructure {
public:
    virtual ~IMicrostructure() = default;
    virtual void apply(Tick& tick, std::mt19937_64& rng) = 0;
};

class BasicSpread : public IMicrostructure {
public:
    struct Config {
        double spread_bps = 5.0;  // 5 basis points
        double spread_stddev_bps = 2.0;
        int min_lot_size = 100;
        int max_lot_size = 10000;
    };
    // ... implementation
};

// Includes order book simulation
class OrderBookModel : public IMicrostructure {
public:
    struct Config {
        int max_depth = 10;
        double spread_bps = 5.0;
        double skewness = 0.0;  // Bid/ask imbalance
    };
    // ... implementation
};
} // namespace tickstream::microstructure
```

**Producer Class:**
```cpp
namespace tickstream {

class Producer {
public:
    struct Config {
        std::string symbol;
        std::unique_ptr<process::IProcess> price_process;
        std::unique_ptr<schedule::IScheduler> scheduler;
        std::unique_ptr<microstructure::IMicrostructure> microstructure;
        double initial_price = 100.0;
        uint64_t initial_sequence = 0;
    };
    
    explicit Producer(Config config);
    
    // Generate next tick
    std::optional<Tick> generate_next();
    
    // Generate N ticks ahead
    std::vector<Tick> generate_batch(size_t count);
    
    // Reset to initial state
    void reset();
    
    // Time control
    void set_time_multiplier(double multiplier);  // 1.0 = real-time
    void jump_to_time(Timestamp time);
    
    const Config& config() const noexcept;
};
} // namespace tickstream
```

### 4.4 `consumer.hpp` - Tick Processing

```cpp
namespace tickstream {

// Base consumer interface
class IConsumer {
public:
    virtual ~IConsumer() = default;
    virtual void on_tick(const Tick& tick) = 0;
    virtual void on_error(const std::exception& e) = 0;
    virtual void on_completed() = 0;
};

// Concrete implementations
class ConsoleConsumer : public IConsumer {
public:
    explicit ConsoleConsumer(std::ostream& os = std::cout);
    void on_tick(const Tick& tick) override;
    // ... implementation
};

class CSVConsumer : public IConsumer {
public:
    explicit CSVConsumer(const std::filesystem::path& filepath,
                         bool write_header = true);
    // ... implementation
};

class AggregatingConsumer : public IConsumer {
public:
    struct Config {
        std::chrono::nanoseconds bar_interval = std::chrono::minutes(1);
        std::function<void(const Bar&)> on_bar_complete;
    };
    // ... aggregates ticks to OHLCV bars
};

// Function wrapper consumer
template<typename Fn>
class FunctionConsumer : public IConsumer {
public:
    explicit FunctionConsumer(Fn&& fn) : callback_(std::forward<Fn>(fn)) {}
    void on_tick(const Tick& tick) override { callback_(tick); }
    void on_error(const std::exception& e) override { /* default ignore */ }
    void on_completed() override { /* default nothing */ }
private:
    Fn callback_;
};
} // namespace tickstream
```

### 4.5 `stream.hpp` - Integrated Stream Management

```cpp
namespace tickstream {

class Stream {
public:
    struct Config {
        Producer::Config producer_config;
        size_t buffer_capacity = 65536;  // Ring buffer size
        std::chrono::nanoseconds consumer_timeout = std::chrono::milliseconds(100);
    };
    
    explicit Stream(Config config);
    
    // Add consumers
    void add_consumer(std::shared_ptr<IConsumer> consumer);
    void remove_consumer(std::shared_ptr<IConsumer> consumer);
    
    // Control
    void start();    // Begin async production
    void stop();     // Graceful shutdown
    void pause();
    void resume();
    
    // Synchronous generation (for backtesting)
    void run_for(std::chrono::nanoseconds duration);
    void run_until(Timestamp end_time);
    
    // Statistics
    struct Stats {
        uint64_t ticks_produced;
        uint64_t ticks_consumed;
        uint64_t buffer_overflows;
        std::chrono::nanoseconds total_runtime;
    };
    
    Stats stats() const noexcept;
    
    // Iterators for backtesting
    class iterator;  // Forward iterator over generated ticks
    iterator begin();
    iterator end();
};

// Multi-stream coordinator
class StreamManager {
public:
    void add_stream(std::string name, Stream::Config config);
    void remove_stream(const std::string& name);
    
    void start_all();
    void stop_all();
    
    // Correlated streams
    void add_correlation(const std::string& stream1,
                         const std::string& stream2,
                         double correlation);
    
    std::shared_ptr<Stream> get_stream(const std::string& name);
};
} // namespace tickstream
```

## 5. Usage Examples

### 5.1 Basic Single Stream

```cpp
#include <tickstream/tickstream.hpp>

int main() {
    using namespace tickstream;
    using namespace std::chrono_literals;
    
    // Create a GBM process for AAPL
    auto process = std::make_unique<process::GBM>(
        process::GBM::Config{
            .initial_price = 150.0,
            .mu = 0.08,
            .sigma = 0.25
        }
    );
    
    // Create stream
    Stream stream(Stream::Config{
        .producer_config = Producer::Config{
            .symbol = "AAPL",
            .price_process = std::move(process),
            .scheduler = std::make_unique<schedule::Poisson>(100.0),  // 100 ticks/sec avg
            .microstructure = std::make_unique<microstructure::BasicSpread>(
                microstructure::BasicSpread::Config{
                    .spread_bps = 5.0,
                    .min_lot_size = 100
                }
            )
        }
    });
    
    // Add consumer
    stream.add_consumer(std::make_shared<ConsoleConsumer>());
    
    // Run for 5 seconds
    stream.run_for(5s);
    
    return 0;
}
```

### 5.2 Multi-stream with Correlation

```cpp
auto manager = tickstream::StreamManager();

// Create correlated streams
auto spy = create_stream_config("SPY", gbm_config(420.0, 0.07, 0.18));
var aapl = create_stream_config("AAPL", gbm_config(150.0, 0.10, 0.25));

manager.add_stream("SPY", spy);
manager.add_stream("AAPL", aapl);
manager.add_correlation("SPY", "AAPL", 0.65);  // 65% correlation

// Run in accelerated time
manager.get_stream("SPY")->set_time_multiplier(10.0);  // 10x real-time
manager.start_all();

std::this_thread::sleep_for(30s);
manager.stop_all();
```

### 5.3 Backtesting with Iterator

```cpp
auto stream = tickstream::Stream(config);
auto& producer = stream.producer();

// Generate 100,000 ticks
for (const auto& tick : stream.ticks().take(100'000)) {
    // Strategy logic here
    if (tick.price > upper_band) {
        // Sell signal
    }
}

// Or with time range
auto start = tickstream::Timestamp::from_iso("2024-01-01T09:30:00");
auto end = tickstream::Timestamp::from_iso("2024-01-01T16:00:00");

for (const auto& tick : stream.ticks_between(start, end)) {
    // Process trading day
}
```

## 6. Configuration File Support (JSON)

```json
{
  "streams": {
    "EURUSD": {
      "process": {
        "type": "ou",
        "initial_price": 1.0800,
        "mean": 1.0800,
        "theta": 0.5,
        "sigma": 0.15
      },
      "schedule": {
        "type": "poisson",
        "lambda_per_second": 50.0
      },
      "microstructure": {
        "type": "basic_spread",
        "spread_bps": 0.8
      }
    }
  },
  "time": {
    "start": "2024-01-01T00:00:00Z",
    "end": "2024-01-31T23:59:59Z",
    "multiplier": 1.0
  },
  "output": {
    "format": "csv",
    "directory": "./ticks"
  }
}
```

## 7. Performance Targets

- **Tick generation**: < 100ns per tick (10+ million ticks/second)
- **Memory usage**: < 1MB per stream (excluding buffer)
- **Buffer throughput**: > 50M ticks/second (SPSC ring buffer)
- **Latency**: < 1µs producer-to-consumer (in-process)

## 8. Build Integration

**CMake:**
```cmake
# Option 1: Add as subdirectory
add_subdirectory(tickstream)

# Option 2: FetchContent
include(FetchContent)
FetchContent_Declare(tickstream
    GIT_REPOSITORY https://github.com/username/tickstream.git
    GIT_TAG v1.0.0
)
FetchContent_MakeAvailable(tickstream)

target_link_libraries(your_target PRIVATE tickstream::tickstream)
```

## 9. Testing Strategy

1. **Unit Tests**: Each process model (GBM, OU, etc.)
2. **Integration Tests**: Producer-consumer pipelines
3. **Performance Tests**: Throughput and latency benchmarks
4. **Determinism Tests**: Same seed produces same output
5. **Memory Tests**: No leaks in long-running streams

## 10. Roadmap

### Phase 1 (MVP)
- GBM and OU processes
- Basic spread microstructure
- CSV and console output
- Single stream operation

### Phase 2
- Jump processes (Merton, Kou)
- Order book simulation
- Trading calendar
- Multi-stream correlation
- FIX protocol output

### Phase 3
- WebSocket server
- Historical data replay
- Advanced statistics
- Python bindings

---

This specification provides a concrete foundation for implementing Tickstream. The modular design allows for incremental implementation while maintaining high performance and flexibility.