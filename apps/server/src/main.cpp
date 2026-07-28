// apps/server/src/main.cpp

#include "transport/sender.hpp"

#include <cstdint>
#include <span>
#include <tickstream/core/tick.hpp>

// STL
#include <chrono>
#include <cstdlib>
#include <format>
#include <thread>

int main() {

  constexpr auto localhost = "127.0.0.1";
  server::transport::Sender sender(localhost, 5000);

  auto max_messages{100'000};
  constexpr auto interval = std::chrono::milliseconds(1);

  auto tick = tickstream::core::Tick{
    .seq = 0,
    .exchange_ts = 0,
    .symbol = 999,
    .price = 10,
    .qty = 10,
    .side = 0,
    .type = 0,
    .reserved = 0,
  };

  for (int i{0}; i < max_messages; ++i) {
    auto message = std::format("UDP message: {}\n", i);
    tick.seq = static_cast<uint64_t>(i);

    auto bytes = std::as_bytes(std::span{&tick, 1});
    sender.send(bytes);

    std::this_thread::sleep_for(interval);
  };

  return EXIT_SUCCESS;
}
