// tickstream/include/tickstream/types/price.hpp

#pragma once

#include "tickstream/types/base/type.hpp"

namespace tickstream::types {

struct PriceTag {};
using Price = StrongType<double, PriceTag, Addable, Subtractable>;
static_assert(validate_strong_type<Price, double>());

} // namespace tickstream::types
