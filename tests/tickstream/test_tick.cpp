// test/tickstream/test_tick.cpp

#define CATCH_CONFIG_MAIN
#include "catch_amalgamated.hpp"
#include <tickstream/tick.hpp>

namespace ts = tickstream; // local alias

TEST_CASE("Tick Creation Test", "[tick]")
{
    // Create two tick instances using the tick_btc function
    auto tick_1 = ts::tick_btc();
    auto tick_2 = ts::tick_btc();

    // Verify that the ticks have been created with expected values
    REQUIRE(tick_1.symbol == "BTC-USD");
    REQUIRE(tick_2.symbol == "BTC-USD");

    // Check that timestamps and prices are set
    REQUIRE(tick_1.unix_ts_ns > 0);
    REQUIRE(tick_2.unix_ts_ns > 0);

    // Check that prices are positive
    REQUIRE(tick_1.price > 0);
    REQUIRE(tick_2.price > 0);
}