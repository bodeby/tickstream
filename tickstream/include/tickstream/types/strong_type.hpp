// tickstream/types/strong_type.hpp

#pragma once

#include <compare>
#include <functional>
#include <ostream>
#include <type_traits>

namespace tickstream {

// ------ CRTP Mixins ------

template <typename Derived> struct Addable {
  friend constexpr Derived
  operator+(const Derived &lhs, const Derived &rhs) noexcept {
    return Derived{lhs.raw() + rhs.raw()};
  }
};

template <typename Derived> struct Subtractable {
  friend constexpr Derived
  operator-(const Derived &lhs, const Derived &rhs) noexcept {
    return Derived{lhs.raw() - rhs.raw()};
  }
};

template <typename Derived> struct Multipliable {
  friend constexpr Derived
  operator*(const Derived &lhs, typename Derived::value_type rhs) noexcept {
    return Derived{lhs.raw() * rhs};
  }
};

template <typename Derived> struct Incrementable {
  constexpr Derived &operator++() noexcept {
    auto &self = static_cast<Derived &>(*this);
    self = Derived{self.raw() + 1};
    return self;
  }

  constexpr Derived operator++(int) noexcept {
    auto copy = static_cast<Derived &>(*this);
    ++(*this);
    return copy;
  }
};

template <typename Derived> struct Printable {
  friend std::ostream &operator<<(std::ostream &os, const Derived &value) {
    return os << value.raw();
  }
};

template <typename Derived> struct Hashable {
  struct Hasher {
    std::size_t operator()(const Derived &v) const noexcept {
      return std::hash<typename Derived::value_type>{}(v.raw());
    }
  };
};

// ------ Template Class ------

template <typename T, typename Tag, template <typename> typename... Skills>
class StrongType : public Skills<StrongType<T, Tag, Skills...>>... {
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

} // namespace tickstream

namespace std {

template <typename T, typename Tag>
struct hash<tickstream::StrongType<T, Tag>> {
  auto operator()(const tickstream::StrongType<T, Tag> &value) const noexcept
    -> std::size_t {
    return std::hash<T>{}(value.raw());
  }
};

} // namespace std
