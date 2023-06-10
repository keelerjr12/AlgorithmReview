#include <iostream>
#include "chp15.h"

int main(int argv, char** argc) {

  std::vector<int> mat_dims { 5, 10, 3, 12, 5, 50, 6};
  //std::vector<int> mat_dims { 2, 3, 5, 6};
  const auto cost = top_down_matrix_chain_order(mat_dims);
  std::cout << cost << std::endl;

  return 0;
}
