// tickstream/process/spread.hpp

#pragma once

#include "process.hpp"

namespace tickstream::process {

class SpreadProcess : public Process<double> {

public:
  double next() override;

private:
  double value_{100};
};

} // namespace tickstream::process
