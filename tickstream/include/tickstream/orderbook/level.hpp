// tickstream/orderbook/level.hpp

#pragma once

#include <tickstream/types/base.hpp>

namespace tickstream::orderbook {

struct Level {
  Price price;       // 4
  Quantity quantity; // 4
};

} // namespace tickstream::orderbook
