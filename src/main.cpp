// Created by @bodeby on 03/10/2025.

#include <iostream>
#include <ostream>

#include <tickstream/tick.hpp>
#include <tickstream/params.hpp>
#include <tickstream/stream_gen.hpp>

void tick_btc()
{
    auto ts1 = tickstream::Tick();
    ts1.symbol = "bitcoin";
    ts1.price = 119200.0;
    ts1.seq = 0;
    ts1.ts = std::chrono::steady_clock::now();
    ts1.regime = 0;

    std::cout << "Latest tick: " << ts1.price << std::endl;
}

void tick_eth()
{
    auto ts2 = tickstream::Tick();
    ts2.symbol = "ethereum";
    ts2.price = 4099.71;
    ts2.seq = 0;
    ts2.ts = std::chrono::steady_clock::now();
    ts2.regime = 0;

    std::cout << "Latest tick: " << ts2.price << std::endl;
}

int main()
{
    tick_btc();
    tick_eth();
}