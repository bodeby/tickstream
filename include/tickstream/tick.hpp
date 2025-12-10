// include/tickstream/tick.hpp

#pragma once

#include <vector>
#include <string>
#include <utility>
#include <chrono>
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

        bool is_snapshot = false;
        std::vector<std::pair<double, double>> bids;
        std::vector<std::pair<double, double>> asks;
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
        << ", is_snapshot=" << t.is_snapshot;

        os << ", bids=[";
        for (const auto& [p, q] : t.bids) os << "(" << p << "," << q << ")";
        os << "], asks=[";
        for (const auto& [p, q] : t.asks) os << "(" << p << "," << q << ")";
        os << "]}";

        return os;
    }

    // create sample tick for BTC-USD
    inline Tick tick_btc() {
        using namespace std::chrono;

        auto sys_raw = time_point_cast<nanoseconds>(system_clock::now())
                        .time_since_epoch()
                        .count();

        auto mono_raw = time_point_cast<nanoseconds>(steady_clock::now())
                        .time_since_epoch()
                        .count();

        const std::uint64_t sys_ts  = static_cast<std::uint64_t>(sys_raw);
        const std::uint64_t mono_ts = static_cast<std::uint64_t>(mono_raw);

        return Tick{
            .symbol = "BTC-USD",
            .price = 65000.0,
            .volume = 1.5,
            .bid = 64999.5,
            .ask = 65000.5,
            .unix_ts_ns = sys_ts,
            .mono_ts_ns = mono_ts,
            .sequence = 0,
            .is_snapshot = false,
            .bids = {},
            .asks = {}
        };
    };

} // namespace tickstream
