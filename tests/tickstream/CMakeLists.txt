# ------------------------------------------------------------------
# GTEST SETUP
# ------------------------------------------------------------------

include(GoogleTest)

# ------------------------------------------------------------------
# ORDERBOOK
# ------------------------------------------------------------------

add_executable(orderbook_tests
  orderbook/order_test.cpp
)

target_link_libraries(orderbook_tests
  PRIVATE GTest::gtest_main tickstream
)

gtest_discover_tests(orderbook_tests)
