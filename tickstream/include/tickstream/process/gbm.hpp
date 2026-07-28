// tickstream/include/tickstream/process/gbm.hpp

#include "tickstream/process/process.hpp"

#include <cmath>
#include <random>

namespace tickstream {

/**
*  Process : Geometric Brownian Motion
*/

struct GBMParams {
  double s0;
  double mu;
  double sigma;
  double dt;
  std::uint64_t seed = std::random_device{}();
};

class GBM final : public Process<double> {
public:
  GBM(const GBMParams &params)
      : s_(params.s0),
        mu_(params.mu),
        sigma_(params.sigma),
        dt_(params.dt),
        rng_(params.seed),
        normal_(0.0, 1.0) {};

  double next() override {
    const double z = normal_(rng_);
    const auto lhs = (mu_ - 0.5 * sigma_ * sigma_) * dt_;
    const auto rhs = sigma_ * std::sqrt(dt_) * z;
    s_ *= std::exp(lhs + rhs);
    return s_;
  };

private:
  double s_;
  double mu_;
  double sigma_;
  double dt_;

  std::mt19937_64 rng_;
  std::normal_distribution<double> normal_;
};

} // namespace tickstream
