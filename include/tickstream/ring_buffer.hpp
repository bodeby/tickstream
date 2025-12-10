// include/tickstream/ring_bufffer.hpp

#pragma once

#include <atomic>    // dor thread-safe sequence counter
#include <vector>    // buffer for batch processing
#include <cstddef>   // for std::size_t (portable size type)

namespace tickstream
{
    /// SPSC ring buffer concept for decoupled producer/consumer.
    template <typename T>
    class RingBuffer {
    public:
        explicit RingBuffer(std::size_t capacity) 
            : buffer_(capacity)
            , capacity_(capacity)
            , head_(0)
            , tail_(0) {}

        ~RingBuffer() = default;

        // non-blocking, lock-free friendly
        bool try_push(const T &item) {
            if (size_.load(std::memory_order_acquire) >= capacity_) {
                return false; // Buffer is full
            }
            
            buffer_[tail_] = item;
            tail_ = (tail_ + 1) % capacity_;
            size_.fetch_add(1, std::memory_order_release);
            return true;
        }; 

        bool try_pop(T& item) {
            if (size_.load(std::memory_order_acquire) == 0) {
                return false; // Buffer is empty
            }
            
            item = buffer_[head_];
            head_ = (head_ + 1) % capacity_;
            size_.fetch_sub(1, std::memory_order_release);
            return true;
        }

        // total capacity of the buffer
        std::size_t capacity() const {
            return capacity_;
        };

        // current size of the buffer
        std::size_t size() const {
            return size_.load(std::memory_order_relaxed);
        }

        // utility to check if buffer is empty
        bool empty() const {
            return size() == 0;
        }

        // utility to check if buffer is full
        bool full() const {
            return size() == capacity_;
        }

        // utility to clear the buffer
        void clear() {
            head_ = 0;
            tail_ = 0;
            size_.store(0, std::memory_order_release);
        }


    private:
        std::vector<T> buffer_;
        const std::size_t capacity_;
        std::size_t head_; // read position
        std::size_t tail_; // write position
        std::atomic<std::size_t> size_; // current size

    };

}