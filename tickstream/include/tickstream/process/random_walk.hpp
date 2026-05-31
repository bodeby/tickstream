// tickstream/process/random_walk.hpp

#pragma once

#include "process.hpp"

namespace tickstream::process {

class RandomWalkProcess : public Process<double> {

public:
  double next() override;

private:
  double value_{100};
};

} // namespace tickstream::process
