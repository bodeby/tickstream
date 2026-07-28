// tickstream/include/tickstream/core/rng.hpp

#pragma once

#include <cstdint>
#include <random>

namespace tickstream::core {

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

} // namespace tickstream::core
