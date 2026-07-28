// include/tickstream/stream_gen.hpp

#pragma once

#include "tickstream/tick.hpp"
#include "tickstream/types/params.hpp"

#include <cstddef>
#include <functional>
#include <memory>

namespace tickstream {

/// Pseudo tick stream engine. pImpl hides model details.
class Generator {
public:
  explicit Generator(const Params &params);
  ~Generator();

  Generator(const Generator &) = delete;            // copy
  Generator &operator=(const Generator &) = delete; // copy assignement

  Generator(Generator &&) noexcept;            // move operator
  Generator &operator=(Generator &&) noexcept; // move assigment

  // Pull model: single-step generation.
  Tick next();

  // Push model: call sink at target rate. count=0 => unbounded.
  void run(const std::function<void(const Tick &)> &sink, std::size_t count = 0);

  // Control
  void set_rate_hz(double hz);
  double rate_hz() const;

  // Introspection
  const Params &params() const;

private:
  struct Impl;
  std::unique_ptr<Impl> p_;
};
} // namespace tickstream
