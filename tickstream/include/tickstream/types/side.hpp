// tickstream/types/side.hpp

#pragma once

#include <cstdint>

namespace tickstream::types {

enum class Side : std::uint8_t { Bid, Ask };

enum class Event : std::uint8_t { Trade, Quote, Update };

} // namespace tickstream::types
