#include <gtest/gtest.h>
#include "chp15.h"
#include <vector>

TEST(DynamicProgramming, rod_cut_td_naive_no_cut_returns_max_revenue) {

  std::vector<int> prices {0, 0, 0, 0, 10};

  const auto size = 5;
  const auto EXP_REV = 10;

  const auto revenue = rod_cut_td_naive(prices, size);

  EXPECT_EQ(EXP_REV, revenue);
}

TEST(DynamicProgramming, rod_cut_td_memoization_no_cut_returns_max_revenue) {

  std::vector<int> prices {0, 0, 0, 0, 10};

  const auto size = 5;
  const auto EXP_REV = 10;

  const auto revenue = rod_cut_td_memoization(prices, size);

  EXPECT_EQ(EXP_REV, revenue);
}

TEST(DynamicProgramming, rod_cut_bu_no_cut_returns_max_revenue) {

  std::vector<int> prices {0, 0, 0, 0, 10};

  const auto size = 5;
  const auto EXP_REV = 10;

  const auto revenue = rod_cut_bu(prices, size);

  EXPECT_EQ(EXP_REV, revenue);
}
