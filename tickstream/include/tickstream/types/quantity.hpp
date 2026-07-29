// tickstream/include/tickstream/types/quantity.hpp

#pragma once

#include "tickstream/types/base/type.hpp"

#include <cstdint>

namespace tickstream::types {

struct QuantityTag {};
using Quantity = StrongType<std::uint32_t, QuantityTag, Addable, Subtractable>;
static_assert(validate_strong_type<Quantity, std::int32_t>());

} // namespace tickstream::types
