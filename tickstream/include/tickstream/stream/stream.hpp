// tickstream/include/tickstream/stream/stream.hpp

#include "tickstream/core/tick.hpp"
#include "tickstream/process/process.hpp"

#include <chrono>

namespace tickstream {

template <typename Process> class Stream {
public:
  Stream(Process process, double flow_rate_hz)
      : process_(std::move(process)),
        next_(Clock::now()),
        interval_(std::chrono::duration<double>(1.0 / flow_rate_hz)) {};

  std::optional<core::Message> next() {
    auto now = Clock::now();
    if (now < next_) return std::nullopt;

    next_ += interval_;
    return process_.next();
  }

private:
  using Clock = std::chrono::steady_clock;

  Process process_;
  Clock::time_point next_;
  Clock::duration interval_;
};

} // namespace tickstream
