#include <iostream>
#include <string>
#include "chp13.h"

int main() {
  keeler::RbTree<int, int> tree;

  tree.insert({2, 2});
  tree.insert({3, 3});
  tree.insert({1, 1});
  tree.insert({0, 0});

  std::cout << tree.size() << std::endl;

  for (auto it = tree.begin(); it != tree.end(); ++it) {
    std::cout << "(" << it->first << ", " << it->second << "), ";
  }

  std::cout << "\n";

  for (auto it = tree.preorder_begin(); it != tree.preorder_end(); ++it) {
    std::string spacing(2*it.depth(), ' ');
    std::cout << spacing << "(" << it->first << ", " << it->second << ")";
    if (it.color() == keeler::detail::Color::BLACK) {
      std::cout << "BLACK\n";
    } else {
      std::cout << "RED\n";
    }
  }


  return 0;
}
