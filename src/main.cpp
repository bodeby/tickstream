// Created by @bodeby on 03/10/2025.

#include <iostream>
#include <ostream>
#include <vector>

// internal includes
#include <tickstream/tick.hpp>
#include <tickstream/params.hpp>
#include <tickstream/ring_buffer.hpp>
#include <tickstream/producer.hpp>
#include <tickstream/consumer.hpp>
#include <tickstream/stream_manager.hpp>

namespace ts = tickstream;                      // local alias

using TickBuffer   = ts::RingBuffer<ts::Tick>;  // semantic alias
using TickConsumer = ts::Consumer<ts::Tick>;    // semantic alias
using TickProducer = ts::Producer<ts::Tick>;    // semantic alias

int main()
{
    TickBuffer ring_buffer(1024); // Create a ring buffer with capacity 1024 (stack allocated)
    TickConsumer consumer();
    TickProducer producer();

    auto tick_1 = ts::tick_btc();
    auto tick_2 = ts::tick_btc();

    std::cout << tick_1 << "\n";
    std::cout << tick_2 << "\n";

    bool pushed_1 = ring_buffer.try_push(tick_1);
    bool pushed_2 = ring_buffer.try_push(tick_2);

    std::cout << "Pushed BTC tick: " << (pushed_1 ? "success" : "failure") << "\n";
    std::cout << "Pushed ETH tick: " << (pushed_2 ? "success" : "failure") << "\n";
    std::cout << "Ring buffer size after pushes: " << ring_buffer.size() << "\n";

    bool popped_1 = ring_buffer.try_pop(tick_1);
    bool popped_2 = ring_buffer.try_pop(tick_2);

    std::cout << "Popped BTC tick: " << (popped_1 ? "success" : "failure") << "\n";
    std::cout << "Popped ETH tick: " << (popped_2 ? "success" : "failure") << "\n";
    std::cout << "Ring buffer size after pops: " << ring_buffer.size() << "\n";

    bool pushed_3 = ring_buffer.try_push(tick_1);
    ring_buffer.clear(); // Clear the buffer
    std::cout << "Ring buffer size after clear: " << ring_buffer.size() << "\n";
    std::cout << "Popped tick price: " << tick_1.price << "\n";

    auto manager = ts::stream::StreamManager();

    std::vector<int> numbers = {1, 7, 3, 5, 9, 2};

    for (int num : numbers) {
        manager.add_stream(num);
    }
};