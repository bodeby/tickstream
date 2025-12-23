// tests/test_order.cpp - Start with this
#define CATCH_CONFIG_MAIN
#include "catch_amalgamated.hpp"

// internal includes
#include <tickstream/tick.hpp>

namespace ts = tickstream; // local alias

TEST_CASE("Tick Creation Test", "[tick]")
{
    auto tick_1 = ts::tick_btc();
    auto tick_2 = ts::tick_btc();

    REQUIRE(tick_1.symbol == "BTC-USD");
    REQUIRE(tick_2.symbol == "BTC-USD");
    REQUIRE(tick_1.unix_ts_ns > 0);
    REQUIRE(tick_2.unix_ts_ns > 0);
    REQUIRE(tick_1.price > 0);
    REQUIRE(tick_2.price > 0);
}