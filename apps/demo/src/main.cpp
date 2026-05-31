// apps/demo/main.cpp

#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <ostream>

// library includes
#include <tickstream/generator.hpp>
#include <tickstream/tick.hpp>
#include <tickstream/transport/consumer.hpp>
#include <tickstream/transport/producer.hpp>
#include <tickstream/transport/spsc.hpp>
#include <tickstream/types/params.hpp>

namespace ts = tickstream; // local alias

using TickBuffer = ts::SPSC<ts::Tick>;       // semantic alias
using TickConsumer = ts::Consumer<ts::Tick>; // semantic alias
using TickProducer = ts::Producer<ts::Tick>; // semantic alias

constexpr static std::size_t buffer_size{1024};

int main() {
  TickBuffer tick_queue(buffer_size);
  TickConsumer consumer();
  TickProducer producer();

  auto tick_1 = ts::tick_btc();
  auto tick_2 = ts::tick_btc();

  std::cout << tick_1 << "\n";
  std::cout << tick_2 << "\n";

  tick_queue.try_push(tick_1);
  tick_queue.try_push(tick_2);

  std::cout << "Ring buffer size after pushes: " << tick_queue.size() << "\n";

  tick_queue.try_pop(tick_1);
  tick_queue.try_pop(tick_2);

  std::cout << "Ring buffer size after pops: " << tick_queue.size() << "\n";

  bool pushed_3 = tick_queue.try_push(tick_1);

  if (!pushed_3) {
    return EXIT_FAILURE;
  }

  tick_queue.clear(); // Clear the buffer

  std::cout << "Ring buffer size after clear: " << tick_queue.size() << "\n";
  std::cout << "Popped tick price: " << tick_1.price << "\n";

  return EXIT_SUCCESS;
};
