#include <gtest/gtest.h>
#include "chp15.h"
#include <vector>

TEST(DynamicProgramming, naive_top_down_recursive_rod_cut_no_cut_returns_max_revenue) {

  std::vector<int> prices {0, 0, 0, 0, 10};

  const auto size = 5;
  const auto EXP_REV = 10;

  const auto revenue = naive_top_down_recursive_rod_cut(prices, size);

  EXPECT_EQ(EXP_REV, revenue);
}

TEST(DynamicProgramming, top_down_memoization_recursive_rod_cut_no_cut_returns_max_revenue) {

  std::vector<int> prices {0, 0, 0, 0, 10};

  const auto size = 5;
  const auto EXP_REV = 10;

  const auto revenue = top_down_memoization_rod_cut(prices, size);

  EXPECT_EQ(EXP_REV, revenue);
}

TEST(DynamicProgramming, bottom_up_rod_cut_no_cut_returns_max_revenue) {

  std::vector<int> prices {0, 0, 0, 0, 10};

  const auto size = 5;
  const auto EXP_REV = 10;

  const auto revenue = bottom_up_rod_cut(prices, size);

  EXPECT_EQ(EXP_REV, revenue);
}
