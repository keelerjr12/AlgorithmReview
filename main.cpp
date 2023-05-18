#include <iostream>
#include <string>
#include "chp13.h"

template<typename Key, typename T>
void preorder_print(keeler::RbTree<Key, T>& tree);

int main() {
  keeler::RbTree<int, int> tree;

  tree.insert({3, 3});
  preorder_print(tree);
  tree.insert({1, 1});
  preorder_print(tree);
  tree.insert({5, 5});
  preorder_print(tree);
  tree.insert({0, 0});
  preorder_print(tree);
  tree.insert({6, 6});
  preorder_print(tree);
  tree.insert({2, 2});
  preorder_print(tree);
  tree.insert({4, 4});
  preorder_print(tree);
  tree.insert({7, 7});
  preorder_print(tree);
  
  std::cout << tree.size() << std::endl;

  for (auto it = tree.begin(); it != tree.end(); ++it) {
    std::cout << "(" << it->first << ", " << it->second << "), ";
  }

  std::cout << "\n";


  return 0;
}

template<typename Key, typename T>
void preorder_print(keeler::RbTree<Key, T>& tree) {
  for (auto it = tree.preorder_begin(); it != tree.preorder_end(); ++it) {
    std::string spacing(2*it.depth(), ' ');
    std::cout << spacing << "(" << it->first << ", " << it->second << ")";
    if (it.color() == keeler::detail::Color::BLACK) {
      std::cout << "BLACK\n";
    } else {
      std::cout << "RED\n";
    }
  }

  std::cout << "\n";
}
