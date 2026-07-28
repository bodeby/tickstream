// tickstream/include/tickstream/core/tick.hpp

#include <cstdint>

namespace tickstream::core {

struct Message {
  std::uint64_t seq;
  std::uint64_t exchange_ts;
  std::uint32_t symbol;
  std::uint32_t price;
  std::uint32_t qty;
  std::uint8_t side; // Bid/Ask
  std::uint8_t type; // Trade, Quote, Update
  std::uint16_t reserved;
};

} // namespace tickstream::core
