// Created by @bodeby on 03/10/2025.

#ifndef TICKSTREAM_TICK_H
#define TICKSTREAM_TICK_H

#pragma once
#include <cstdint>
#include <string>
#include <chrono>

namespace tickstream {
    /// Immutable output record for a simulated market tick.
    struct Tick {
        std::string symbol; // e.g., "AAPL"
        double price; // quantized price
        std::int64_t seq; // monotonic sequence id
        std::chrono::steady_clock::time_point ts; // emission timestamp
        int regime; // hidden state id for validation (e.g., 0/1)
    };
} // namespace tickstream

#endif //TICKSTREAM_TICK_H
