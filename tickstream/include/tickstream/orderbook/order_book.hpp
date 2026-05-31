// tickstream/orderbook/order_book.hpp

#pragma once

#include "tickstream/orderbook/delta.hpp"
#include "tickstream/orderbook/level.hpp"
#include "tickstream/types/base.hpp"

#include <vector>

namespace tickstream::orderbook {

class OrderBook {
public:
  void apply(const BookDelta &delta);

  [[nodiscard]]
  const std::vector<Level> &bids() const noexcept {
    return bids_;
  };

  [[nodiscard]]
  const std::vector<Level> &asks() const noexcept {
    return asks_;
  };

  [[nodiscard]]
  Price best_bid() const noexcept {
    if (bids_.empty()) return Price{0};
    return bids_.front().price;
  };

  [[nodiscard]]
  Price best_ask() const noexcept {
    if (asks_.empty()) return Price{0};
    return asks_.front().price;
  };

private:
  std::vector<Level> bids_;
  std::vector<Level> asks_;
};

} // namespace tickstream::orderbook
