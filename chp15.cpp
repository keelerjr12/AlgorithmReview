#include "chp15.h"
#include <algorithm>
#include <limits>
#include <vector>

#include <iostream>

int naive_top_down_recursive_rod_cut(const std::vector<int>& prices, int n) {
  if (n == 0) {
    return 0;
  }

  auto max_revenue = std::numeric_limits<int>::min();

  for (auto i = 1; i <= n; ++i) {
    const auto revenue = prices[i - 1] + naive_top_down_recursive_rod_cut(prices, n - i);
    max_revenue = std::max(revenue, max_revenue);
  }

  return max_revenue;
}

int top_down_memoization_rod_cut_aux(const std::vector<int>& prices, std::vector<int>& revenues, int n) {
  if (n == 0) {
    return 0;
  }

  if (revenues[n - 1] >= 0) {
    return revenues[n - 1];
  }

  auto max_revenue = std::numeric_limits<int>::min();

  for (auto i = 1; i <= n; ++i) {
    const auto revenue = prices[i - 1] + top_down_memoization_rod_cut_aux(prices, revenues, n - i);
    max_revenue = std::max(revenue, max_revenue);
  }

  revenues[n - 1] = max_revenue;
  return max_revenue;

}

int top_down_memoization_rod_cut(const std::vector<int>& prices, int n) {
  std::vector<int> revenues(n, -1);
  return top_down_memoization_rod_cut_aux(prices, revenues, n);
}
