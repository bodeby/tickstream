// tickstream/include/tickstream/process/side/bernoulli.hpp

#pragma once

#include "tickstream/process/process.hpp"

#include <cstdint>
#include <random>

namespace tickstream::bernoulli {

struct Context {
  std::uint64_t seed = std::random_device{}();
};

} // namespace tickstream::bernoulli

namespace tickstream {

class BernoulliProcess final : public Process<double> {
public:
  BernoulliProcess(const bernoulli::Context &ctx)
      : rng_(ctx.seed) {};

  double next() override {
    const double x = dist_(rng_);
    return x;
  };

private:
  std::mt19937_64 rng_;
  std::bernoulli_distribution dist_{0.5};
};

} // namespace tickstream
