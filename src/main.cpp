// Created by @bodeby on 03/10/2025.

#include <iostream>
#include <ostream>

#include <tickstream/tick.hpp>
#include <tickstream/params.hpp>
#include <tickstream/stream_gen.hpp>
#include <tickstream/ring_buffer/ring_bufffer.hpp>

using tickstream::Tick; // make tick generally available
using tickstream::RingBuffer; // make ring buffer generally available

Tick tick_btc()
{
    auto tick = Tick();
    tick.symbol = "bitcoin";
    tick.price = 119200.0;
    tick.seq = 0;
    tick.ts = std::chrono::steady_clock::now();
    tick.regime = 0;

    std::cout << "Latest tick: " << tick.price << std::endl;

    return tick;
};

Tick tick_eth()
{
    auto tick = Tick();
    tick.symbol = "ethereum";
    tick.price = 4099.71;
    tick.seq = 0;
    tick.ts = std::chrono::steady_clock::now();
    tick.regime = 0;

    std::cout << "Latest tick: " << tick.price << std::endl;

    return tick;
};

int main()
{
    RingBuffer<Tick> ring_buffer(1024);

    Tick tick_1 = tick_btc();
    Tick tick_2 = tick_eth();

    bool pushed_1 = ring_buffer.try_push(tick_1);
    bool pushed_2 = ring_buffer.try_push(tick_2);

    std::cout << "Pushed BTC tick: " << (pushed_1 ? "success" : "failure") << std::endl;
    std::cout << "Pushed ETH tick: " << (pushed_2 ? "success" : "failure") << std::endl;
    std::cout << "Ring buffer size after pushes: " << ring_buffer.size() << std::endl;

    bool popped_1 = ring_buffer.try_pop(tick_1);
    bool popped_2 = ring_buffer.try_pop(tick_2);

    std::cout << "Popped BTC tick: " << (popped_1 ? "success" : "failure") << std::endl;
    std::cout << "Popped ETH tick: " << (popped_2 ? "success" : "failure") << std::endl;
    std::cout << "Ring buffer size after pops: " << ring_buffer.size() << std::endl;

    bool pushed_3 = ring_buffer.try_push(tick_1);
    ring_buffer.clear(); // Clear the buffer
    std::cout << "Ring buffer size after clear: " << ring_buffer.size() << std::endl;
    std::cout << "Popped tick price: " << tick_1.price << std::endl;


};