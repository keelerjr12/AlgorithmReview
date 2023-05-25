#include <iostream>
#include "chp15.h"

int main() {

  std::vector<int> prices {
    1, 5, 8, 9, 10, 17, 17, 20, 24, 30,
   35, 41, 48, 57, 67, 78, 90, 103, 114, 129, 
   145, 162, 180, 199, 219, 240, 262, 285, 309, 334, 
   360
  };
  std::vector<int> revenues(prices.size(), -1);
  const auto size = 30;

  const auto revenue = bottom_up_rod_cut(prices, size);

  std::cout << revenue << "\n";

  return 0;
}
