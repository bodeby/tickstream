// tickstream/orderbook/delta.hpp

#pragma once

#include <tickstream/types/base.hpp>
#include <tickstream/types/side.hpp>

namespace tickstream::orderbook {

struct BookDelta {
  Sequence sequence;   // 8
  Timestamp timestamp; // 8
  Price price;         // 4
  Quantity quantity;   // 4
  Side side;           // 1
}; // 25

} // namespace tickstream::orderbook
