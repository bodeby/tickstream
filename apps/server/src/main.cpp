// apps/server/src/main.cpp

#include "transport/sender.hpp"

// STL
#include <chrono>
#include <cstdlib>
#include <format>
#include <thread>

int main() {

  constexpr auto localhost = "127.0.0.1";
  server::transport::Sender sender(localhost, 5000);

  auto max_messages{100};
  constexpr auto interval = std::chrono::seconds(1);

  for (int i{0}; i < max_messages; ++i) {
      auto message = std::format("UDP message: {}\n", i);
      sender.send(message);
      std::this_thread::sleep_for(interval);
  };

  return EXIT_SUCCESS;
}
