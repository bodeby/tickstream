// tickstream/include/tickstream/generator.hpp

#pragma once

#include "tickstream/tick.hpp"

// STL
#include <cstdint>
#include <random>

namespace tickstream {

template <typename Process> class Generator {
public:
  explicit Generator(Process process)
      : price_(std::move(process)) {}

  Tick next(const std::uint64_t seq) {
    return {
      .seq = seq,
      .exchange_ts = 0,       // _rdtsc
      .price = price_.next(), // process
      .symbol = 999,          // static
      .qty = qty_(rng_),      // distribution
      .side = side_(rng_),    // distribution
      .type = type_(rng_),    // distrubition
    };
  };

private:
  Process price_;
  std::mt19937_64 rng_{42};
  std::poisson_distribution<std::uint32_t> qty_{10};
  std::bernoulli_distribution side_{0.5};
  std::discrete_distribution<std::uint8_t> type_{{80, 15, 5}};
};

} // namespace tickstream
