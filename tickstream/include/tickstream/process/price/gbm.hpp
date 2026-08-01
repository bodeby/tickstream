// tickstream/include/tickstream/process/gbm.hpp

#pragma once

#include "tickstream/process/process.hpp"
#include "tickstream/types/price.hpp"

#include <cmath>
#include <random>

namespace tickstream::gbm {

struct Context {
  double s0;
  double mu;
  double sigma;
  double dt;
  std::uint64_t seed = std::random_device{}();
};

} // namespace tickstream::gbm

namespace tickstream {

/**
*  Process : Geometric Brownian Motion
*/

// class GBM final : public Process<types::Price> {
// public:
//   GBM(const gbm::Context &ctx)
//       : s_(ctx.s0),
//         mu_(ctx.mu),
//         sigma_(ctx.sigma),
//         dt_(ctx.dt),
//         rng_(ctx.seed),
//         normal_(0.0, 1.0) {};
//
//   types::Price next() override {
//     const double z = normal_(rng_);
//     const auto lhs = (mu_ - 0.5 * sigma_ * sigma_) * dt_;
//     const auto rhs = sigma_ * std::sqrt(dt_) * z;
//     s_ *= std::exp(lhs + rhs);
//     return types::Price{s_};
//   };
//
// private:
//   double s_;
//   double mu_;
//   double sigma_;
//   double dt_;
//
//   std::mt19937_64 rng_;
//   std::normal_distribution<double> normal_;
// };

class GBM final : public Process<types::Price> {
public:
  GBM(const gbm::Context& ctx)
      : s_(ctx.s0),
        drift_((ctx.mu - 0.5 * ctx.sigma * ctx.sigma) * ctx.dt),
        diffusion_(ctx.sigma * std::sqrt(ctx.dt)),
        rng_(ctx.seed),
        normal_(0.0, 1.0)
  {}

  types::Price next() override
  {
      const double z = normal_(rng_);
      s_ *= std::exp(drift_ + diffusion_ * z);
      return types::Price{s_};
  }

private:
    double s_;

    double drift_;
    double diffusion_;

    std::mt19937_64 rng_;
    std::normal_distribution<double> normal_;
};


} // namespace tickstream
