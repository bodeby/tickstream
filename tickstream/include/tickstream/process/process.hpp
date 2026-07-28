// tickstream/process/process.hpp

#pragma once

namespace tickstream {

template <typename T> class Process {
public:
  virtual ~Process() = default;
  virtual T next() = 0;
};

} // namespace tickstream::process
