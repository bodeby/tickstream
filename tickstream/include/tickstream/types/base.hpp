// tickstream/include/tickstream/types/base.hpp

#pragma once

#include "strong_type.hpp"

#include <cstdint>

namespace tickstream {

struct PriceTag {};
using Price = StrongType<std::uint32_t, PriceTag, Addable, Subtractable>;
static_assert(validate_strong_type<Price, std::int32_t>());

struct QuantityTag {};
using Quantity = StrongType<std::uint32_t, QuantityTag, Addable, Subtractable>;
static_assert(validate_strong_type<Quantity, std::int32_t>());

struct OrderIdTag {};
using OrderId = StrongType<std::uint64_t, OrderIdTag>;
static_assert(validate_strong_type<OrderId, std::int64_t>());

struct SequenceTag {};
using Sequence = StrongType<std::uint64_t, SequenceTag, Incrementable>;
static_assert(validate_strong_type<Sequence, std::int64_t>());

struct TimestampTag {};
using Timestamp = StrongType<std::uint64_t, TimestampTag>;
static_assert(validate_strong_type<Timestamp, std::int64_t>());

} // namespace tickstream
