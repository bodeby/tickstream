// include/tickstream/params.hpp

#pragma once

#include <string>
#include <vector>
#include <cstdint>

namespace tickstream {

    /// Configuration knobs with safe defaults.
    struct Params {
        // Universe and scheduling
        std::vector<std::string> symbols{"AAPL"};
        double rate_hz{10.0};                // target ticks per second (per stream)
        std::uint64_t seed{0};               // 0 => random_device

        // OU drift: dX = kappa*(mu - X) dt + sigma_{regime} dW + J
        double mu{100.0};
        double kappa{0.5};

        // Regime-switching volatility (two-state Markov chain)
        double sigma0{0.10};
        double sigma1{0.40};
        double p01{0.001};                    // P(0→1) per step
        double p10{0.002};                    // P(1→0) per step

        // Jumps (compound Poisson)
        double lambda_jump{0.01};             // expected jumps per second
        double jump_mean{0.0};
        double jump_std{0.2};

        // Microstructure
        double tick_size{0.01};               // price grid
        double sigma_micro{0.005};            // transient noise std before quantize
        double latency_jitter_ms{2.0};        // scheduling jitter

        // Run control (optional)
        std::size_t max_count{0};             // 0 => unbounded
    };

} // namespace tickstream
