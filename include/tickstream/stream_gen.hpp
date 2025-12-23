// include/tickstream/stream_gen.hpp

#pragma once

#include <functional>
#include <cstddef>
#include <memory>
#include <string>
#include <vector>
#include "tickstream/tick.hpp"
#include "tickstream/params.hpp"

namespace tickstream {

    /// SPSC ring buffer concept for decoupled producer/consumer.
    // template <typename T>
    // class RingBuffer {
    // public:
    //     virtual ~RingBuffer() = default;
    //     virtual bool try_push(const T& item) = 0; // non-blocking, lock-free friendly
    //     virtual std::size_t capacity() const = 0;
    //     virtual std::size_t size() const = 0;
    // };

    /// Pseudo tick stream engine. pImpl hides model details.
    class StreamGen {
    public:
        explicit StreamGen(const Params& params);
        ~StreamGen();
        StreamGen(StreamGen&&) noexcept;
        StreamGen& operator=(StreamGen&&) noexcept;

        // Non-copyable (owns stateful RNG and timing)
        StreamGen(const StreamGen&) = delete;
        StreamGen& operator=(const StreamGen&) = delete;

        // Pull model: single-step generation.
        Tick next();

        // Push model: call sink at target rate. count=0 => unbounded.
        void run(const std::function<void(const Tick&)>& sink, std::size_t count = 0);

        // Push into a user-supplied SPSC ring buffer.
        // void run_to_ring(RingBuffer<Tick>& rb, std::size_t count = 0);

        // Control
        void set_rate_hz(double hz);
        double rate_hz() const;

        // Introspection
        const Params& params() const;

    private:
        struct Impl;
        std::unique_ptr<Impl> p_;
    };
}
