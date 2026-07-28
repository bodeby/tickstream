// include/tickstream/tick.hpp

#pragma once

#include <string>
#include <cstdint>

namespace tickstream {

    struct Tick {
        std::string symbol;
        double price;
        double volume;
        double bid;
        double ask;

        std::uint64_t unix_ts_ns;       // external timestamp (system_clock)
        std::uint64_t mono_ts_ns;       // monotonic timestamp (steady_clock)
        std::uint32_t sequence;
    };

    // stream output operator for Tick
    inline std::ostream& operator<<(std::ostream& os, const Tick& t) {
        os << "Tick{"
        << "symbol=" << t.symbol
        << ", price=" << t.price
        << ", volume=" << t.volume
        << ", bid=" << t.bid
        << ", ask=" << t.ask
        << ", unix_ts_ns=" << t.unix_ts_ns
        << ", mono_ts_ns=" << t.mono_ts_ns
        << ", sequence=" << t.sequence
        << "}";

        return os;
    }

} // namespace tickstream
