#include <iostream>
#include "chp13.h"

int main() {
  keeler::RbTree<int, int> tree;

  tree.insert({2, 4});
  tree.insert({3, 3});

  for (auto it = tree.begin(); it != tree.end(); ++it) {
    std::cout << "(" << it->first << ", " << it->second << "), ";
  }

  std::cout << "\n";

  return 0;
}
