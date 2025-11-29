// Created by @bodeby on 03/10/2025.

#ifndef TICKSTREAM_RNG_H
#define TICKSTREAM_RNG_H

#pragma once
#include <cstdint>
#include <random>

namespace tickstream::detail {
    class RNG {
    public:
        explicit RNG(std::uint64_t seed);
        double normal(double mean, double stddev);
        double uniform(double a, double b);
        int poisson(double lambda_dt);
        std::mt19937_64 &engine(); // for advanced use
    private:
        std::mt19937_64 eng_;
    };
} // namespace tickstream::detail


#endif //TICKSTREAM_RNG_H
