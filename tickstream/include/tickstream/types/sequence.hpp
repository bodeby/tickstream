// tickstream/include/tickstream/types/sequence.hpp

#pragma once

#include "tickstream/types/base/type.hpp"

#include <cstdint>

namespace tickstream::types {

struct SequenceTag {};
using Sequence = StrongType<std::uint64_t, SequenceTag, Incrementable>;
static_assert(validate_strong_type<Sequence, std::int64_t>());

} // namespace tickstream::types
