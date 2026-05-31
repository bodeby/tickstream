// tickstream/orderbook/level.hpp

#pragma once

#include <cstdint>
namespace tickstream::orderbook {

struct Level {
  std::uint32_t price;
  std::uint32_t quantity;
};

} // namespace tickstream::orderbook
