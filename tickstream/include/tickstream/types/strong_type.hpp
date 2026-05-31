// tickstream/types/strong_type.hpp

#pragma once

#include <compare>
#include <functional>
#include <ostream>
#include <type_traits>

namespace vantage::core::types {

template <typename T, typename Tag> class StrongType {
public:
  using value_type = T;

  constexpr StrongType() noexcept = default;
  constexpr explicit StrongType(T value) noexcept
      : value_(value) {}

  [[nodiscard]]
  constexpr auto raw() const noexcept -> T {
    return value_;
  }
  constexpr auto operator==(const StrongType &) const noexcept
    -> bool = default;
  constexpr auto operator<=>(const StrongType &) const noexcept = default;

private:
  T value_{};
};

template <typename T, typename Tag>
auto operator<<(std::ostream &os, const StrongType<T, Tag> &value)
  -> std::ostream & {
  return os << value.raw();
}

template <typename T, typename U>
constexpr auto validate_strong_type() noexcept -> bool {
  static_assert(std::is_trivially_copyable_v<T>);
  static_assert(std::is_standard_layout_v<T>);
  static_assert(sizeof(T) == sizeof(U));
  return true;
}

} // namespace vantage::core::types

namespace std {

template <typename T, typename Tag>
struct hash<vantage::core::types::StrongType<T, Tag>> {
  auto operator()(
    const vantage::core::types::StrongType<T, Tag> &value
  ) const noexcept -> std::size_t {
    return std::hash<T>{}(value.raw());
  }
};

} // namespace std
