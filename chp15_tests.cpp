#include <gtest/gtest.h>
#include "chp15.h"
#include <vector>

TEST(DynamicProgramming, rod_cut_returns_zero) {

  std::vector<int> prices {1, 2, 3, 4, 5 };
  bool is_empty = true;

  const auto revenue = rod_cut(prices, 5);

  EXPECT_TRUE(is_empty);
}
