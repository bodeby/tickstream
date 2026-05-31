// tickstream/orderbook/delta.hpp

#pragma once

#include <cstdint>
#include <tickstream/types/side.hpp>

namespace tickstream::orderbook {

struct alignas(32) BookDelta {
  std::uint64_t sequence;  // 8
  std::uint64_t timestamp; // 8
  std::uint32_t price;     // 4
  std::uint32_t quantity;  // 4
  Side side;               // 1
}; // 25

} // namespace tickstream::orderbook
