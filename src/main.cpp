// Created by @bodeby on 03/10/2025.

#include <iostream>
#include <ostream>

#include <tickstream/tick.hpp>
#include <tickstream/params.hpp>
#include <tickstream/stream_gen.hpp>

int main() {
    // create demo tick
    auto t = tickstream::Tick();
    t.symbol = "bitcoin";
    t.price = 119200.0;
    t.seq = 0;
    t.ts = std::chrono::steady_clock::now();
    t.regime = 0;

    std::cout << "Latest tick: " << t.price << std::endl;
}