#include <iostream>
#include "chp15.h"

int main() {

  std::vector<int> prices {1, 5, 8, 9, 10, 17, 17, 20, 24, 30};
  std::vector<int> revenues(prices.size(), -1);
  const auto size = 9;

  const auto revenue = top_down_memoization_rod_cut(prices, size);

  std::cout << revenue << "\n";

  return 0;
}
