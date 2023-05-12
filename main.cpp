#include <iostream>
#include "chp13.h"

int main() {
  keeler::RbTree<int, int> tree;

  tree.insert({2, 2});
  tree.insert({3, 3});
  tree.insert({1, 1});
  tree.insert({5, 5});
  tree.insert({4, 4});
  tree.insert({7, 7});
  tree.insert({6, 6});

  std::cout << tree.size() << std::endl;

  for (auto it = tree.begin(); it != tree.end(); ++it) {
    std::cout << "(" << it->first << ", " << it->second << "), ";
  }

  std::cout << "\n";

  return 0;
}
