// tickstream/include/tickstream/core/tick.hpp

#pragma once

#include <cstdint>
#include <iomanip>
#include <ostream>

namespace tickstream {

struct Tick {
  std::uint64_t seq;
  std::uint64_t exchange_ts;
  double price;
  std::uint32_t symbol;
  std::uint32_t qty;
  std::uint8_t side; // Bid/Ask
  std::uint8_t type; // Trade, Quote, Update
  std::uint16_t reserved;
};

inline std::ostream &operator<<(std::ostream &os, const Tick &tick) {
  return os << "Tick{"
            << "seq=" << tick.seq << ", ts=" << tick.exchange_ts
            << ", price=" << std::fixed << std::setprecision(4) << tick.price
            << ", symbol=" << tick.symbol << ", qty=" << tick.qty
            << ", side=" << static_cast<unsigned>(tick.side)
            << ", type=" << static_cast<unsigned>(tick.type) << '}';
}

} // namespace tickstream
