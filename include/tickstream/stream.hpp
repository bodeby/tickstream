// tickstream/stream.hpp

#pragma once

#include "ring_buffer.hpp"
#include "producer.hpp"
#include "consumer.hpp"
#include "tick.hpp"
#include <memory>
#include <unordered_map>
#include <string>

namespace tickstream {

class TickStream {
public:
    TickStream(size_t buffer_size = 4096) 
        : buffer_(buffer_size) {}
    
    // Add a symbol to stream
    template<typename Callback>
    void add_symbol(const std::string& symbol, Callback tick_generator, 
                    std::chrono::milliseconds interval = std::chrono::milliseconds(100)) {
        auto producer = std::make_unique<Producer<Tick>>(
            buffer_, 
            tick_generator,
            interval
        );
        producers_[symbol] = std::move(producer);
    }
    
    // Start all producers
    void start() {
        for (auto& [symbol, producer] : producers_) {
            producer->start();
        }
    }
    
    // Stop all producers
    void stop() {
        for (auto& [symbol, producer] : producers_) {
            producer->stop();
        }
    }
    
    // Get the buffer for consumers
    RingBuffer<Tick>& get_buffer() { return buffer_; }
    
    // Get statistics
    struct Stats {
        size_t total_ticks_produced;
        size_t total_ticks_consumed;
        size_t buffer_drops;
    };
    
    Stats get_stats() const { return stats_; }

private:
    RingBuffer<Tick> buffer_;
    std::unordered_map<std::string, std::unique_ptr<Producer<Tick>>> producers_;
    Stats stats_;
};

} // namespace tickstream