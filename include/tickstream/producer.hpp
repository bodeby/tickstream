// include/tickstream/producer.hpp

#pragma once

#include <thread>
#include <functional>
#include "ring_buffer.hpp"
#include "tick.hpp"

namespace tickstream {

    template<typename T>
    class Producer {
    public:
        using Callback = std::function<T()>;
        
        Producer(RingBuffer<T>& buffer, Callback callback, std::chrono::milliseconds interval)
            : buffer_(buffer), callback_(callback), interval_(interval), running_(false) {}
        
        void start() {
            running_ = true;
            thread_ = std::thread([this]() {
                while (running_) {
                    T tick = callback_();
                    while (!buffer_.try_push(tick)) {
                        // Buffer full - wait or drop
                        std::this_thread::sleep_for(std::chrono::microseconds(10));
                    }
                    std::this_thread::sleep_for(interval_);
                }
            });
        }
        
        void stop() {
            running_ = false;
            if (thread_.joinable()) thread_.join();
        }
        
    private:
        RingBuffer<T>& buffer_;
        Callback callback_;
        std::chrono::milliseconds interval_;
        std::thread thread_;
        std::atomic<bool> running_;
    };
}


