// tickstream/include/tickstream/generator_2.hpp

#pragma once

#include "tickstream/tick.hpp"

#include <concepts>
#include <utility>

using Price = double;
using Quantity = double;
using Side = double;
using Event = double;
using Timestamp = double;

namespace tickstream {

template <typename P, typename T>
concept Process = requires(P p) {
  { p.next() } -> std::same_as<T>;
};

template <
  Process<Price> PriceModel,
  Process<Quantity> QuantityModel,
  Process<Side> SideModel,
  Process<Event> EventModel,
  Process<Timestamp> TimestampModel>
class Generator {

  explicit Generator(
    PriceModel price,
    QuantityModel quantity,
    SideModel side,
    EventModel event,
    TimestampModel timestamp
  )
      : price_(std::move(price)),
        quantity_(std::move(quantity)),
        side_(std::move(side)),
        event_(std::move(event)),
        timestamp_(std::move(timestamp)) {}

  Tick next(const std::uint64_t seq) {
    return {
      .seq = seq,
      .exchange_ts = timestamp_.next(), // _rdtsc
      .price = price_.next(),           // process
      .symbol = 999,                    // static
      .qty = quantity_.next(),          // process
      .side = side_.next(),             // process
      .type = event_.next(),            // process
    };
  };

private:
  PriceModel price_;
  QuantityModel quantity_;
  SideModel side_;
  EventModel event_;
  TimestampModel timestamp_;
};

} // namespace tickstream
