// tickstream/include/tickstream/types/timestamp.hpp

#pragma once

#include "tickstream/types/base/type.hpp"

#include <cstdint>

namespace tickstream::types {

struct TimestampTag {};
using Timestamp = StrongType<std::uint64_t, TimestampTag>;
static_assert(validate_strong_type<Timestamp, std::int64_t>());

} // namespace tickstream::types
