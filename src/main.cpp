// Created by @bodeby on 03/10/2025.

#include <iostream>
#include <ostream>

#include <tickstream/tick.hpp>
#include <tickstream/params.hpp>
#include <tickstream/stream_gen.hpp>

using tickstream::Tick; // make tick generally available

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
    Tick _tick_1 = tick_btc();
    Tick _tick_2 = tick_eth();
};