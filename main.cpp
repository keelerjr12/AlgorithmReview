#include <iostream>
#include <string>
#include "chp13.h"

<<<<<<< HEAD
template<typename Key, typename T>
void preorder_print(keeler::RbTree<Key, T>& tree);

=======
>>>>>>> 5438969caa2f114f83f29f86c13bcfe670100506
int main() {
  keeler::RbTree<int, int> tree;

  tree.insert({3, 3});
<<<<<<< HEAD
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
=======
  tree.insert({1, 1});
  tree.insert({5, 5});
  tree.insert({0, 0});
  tree.insert({6, 6});
  tree.insert({2, 2});
  tree.insert({4, 4});
  tree.insert({7, 7});
>>>>>>> 5438969caa2f114f83f29f86c13bcfe670100506
  
  std::cout << tree.size() << std::endl;

  for (auto it = tree.begin(); it != tree.end(); ++it) {
    std::cout << "(" << it->first << ", " << it->second << "), ";
  }

  std::cout << "\n";

<<<<<<< HEAD

  return 0;
}

template<typename Key, typename T>
void preorder_print(keeler::RbTree<Key, T>& tree) {
=======
>>>>>>> 5438969caa2f114f83f29f86c13bcfe670100506
  for (auto it = tree.preorder_begin(); it != tree.preorder_end(); ++it) {
    std::string spacing(2*it.depth(), ' ');
    std::cout << spacing << "(" << it->first << ", " << it->second << ")";
    if (it.color() == keeler::detail::Color::BLACK) {
      std::cout << "BLACK\n";
    } else {
      std::cout << "RED\n";
    }
  }

<<<<<<< HEAD
  std::cout << "\n";
=======

  return 0;
>>>>>>> 5438969caa2f114f83f29f86c13bcfe670100506
}
