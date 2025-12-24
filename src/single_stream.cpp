
// #include <tickstream/producer_new.hpp>
#include <tickstream/stream.hpp>


Stream::config create_config() {
    Stream::Config config;
    config.producer_config.symbol = "AAPL";
    config.producer_config.price_process = std::make_unique<process::GBM>(
        process::GBM::Config{
            .initial_price = 150.0,
            .mu = 0.08,
            .sigma = 0.25
        }
    );
    config.producer_config.scheduler = std::make_unique<schedule::Poisson>(100.0); // 100 ticks/sec avg
    config.producer_config.microstructure = std::make_unique<microstructure::BasicSpread>(
        microstructure::BasicSpread::Config{
            .spread_bps = 5.0,
            .min_lot_size = 100
        }
    );

    return config;
}

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

    auto config = create_config();
    
    // Create stream
    Stream stream(config);
    
    // Add consumer
    stream.add_consumer(std::make_shared<ConsoleConsumer>());
    
    // Run for 5 seconds
    stream.run_for(5s);
    
    return 0;
}