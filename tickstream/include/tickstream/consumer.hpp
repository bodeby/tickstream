// include/tickstream/consumer.hpp
#pragma once

#include "ring_buffer.hpp"
#include "tick.hpp"
#include <functional>
#include <vector>

namespace tickstream {

    template<typename T>
    class Consumer {
    public:
        using Handler = std::function<void(const T&)>;
        
        void subscribe(Handler handler) {
            handlers_.push_back(handler);
        }
        
        void process(RingBuffer<T>& buffer) {
            T tick;
            while (buffer.try_pop(tick)) {
                for (auto& handler : handlers_) {
                    handler(tick);
                }
            }
        }
        
        void process_continuous(RingBuffer<T>& buffer, std::atomic<bool>& running) {
            while (running) {
                process(buffer);
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
            }
        }

    private:
        std::vector<Handler> handlers_;
    };

} // namespace tickstream