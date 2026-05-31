// tickstream/orderbook/order_book.hpp

#pragma once

#include "tickstream/orderbook/delta.hpp"
#include "tickstream/orderbook/level.hpp"

#include <vector>

namespace tickstream::orderbook {

class OrderBook {
public:
  void apply(const BookDelta &delta);

  const std::vector<Level> &bids() const noexcept;
  const std::vector<Level> &asks() const noexcept;

  double best_bid() const noexcept;
  double best_ask() const noexcept;

private:
  std::vector<Level> bids_;
  std::vector<Level> asks_;
};

} // namespace tickstream::orderbook
