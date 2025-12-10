// include/tickstream/tick.hpp

#pragma once

#include <cstdint>
#include <string>
#include <chrono>

namespace tickstream {

    /* immutable output record for a simulated market tick. */

    struct Tick {
        std::string symbol;                         // e.g., "AAPL"
        double price;                               // quantized price
        std::int64_t seq;                           // monotonic sequence id
        std::chrono::steady_clock::time_point ts;   // emission timestamp
        int regime;                                 // hidden state id for validation (e.g., 0/1)
    }; /// 
}
