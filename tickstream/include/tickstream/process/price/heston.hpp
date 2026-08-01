// tickstream/include/tickstream/process/heston.hpp

#pragma once

#include "tickstream/process/process.hpp"
#include "tickstream/types/price.hpp"

#include <cmath>
#include <random>

/**
*  Process : Heston
*/

namespace tickstream::heston {

struct Context {
  double s0;    // initial price
  double v0;    // initial variance
  double mu;    // annual drift
  double kappa; // mean reversion
  double theta; // long-run variance
  double xi;    // vol of vol
  double rho;   // correlation [-1,1]
  double dt;
  std::uint64_t seed = std::random_device{}();
};

} // namespace tickstream::heston

namespace tickstream {

class Heston final : public Process<types::Price> {
public:
  Heston(const heston::Context &ctx)
      : s_(ctx.s0),
        v_(ctx.v0),
        mu_(ctx.mu),
        kappa_(ctx.kappa),
        theta_(ctx.theta),
        xi_(ctx.xi),
        rho_(ctx.rho),
        dt_(ctx.dt),
        rng_(ctx.seed) {};

  types::Price next() override {
    const double z1 = normal_(rng_);
    const double z2 = normal_(rng_);

    const double w1 = z1;
    const double w2 = rho_ * z1 + std::sqrt(1.0 - rho_ * rho_) * z2;

    // Full truncation to keep variance positive
    const double vp = std::max(v_, 0.0);
    v_ += kappa_ * (theta_ - vp) * dt_ + xi_ * std::sqrt(vp * dt_) * w2;
    v_ = std::max(v_, 0.0);
    s_ *= std::exp((mu_ - 0.5 * vp) * dt_ + std::sqrt(vp * dt_) * w1);

    return types::Price{s_};
  };

private:
  double s_;
  double v_;
  double mu_;
  double kappa_;
  double theta_;
  double xi_;
  double rho_;
  double dt_;

  std::mt19937_64 rng_;
  std::normal_distribution<double> normal_{0.0, 1.0};
};

} // namespace tickstream
