#include <gtest/gtest.h>
#include "chp13.h"

#include <utility>

TEST(RbTree, tree_empty_returns_empty_true) {
  keeler::RbTree<int, int> tree;

  const auto is_empty = tree.empty();

  EXPECT_TRUE(is_empty);
}

TEST(RbTree, tree_empty_size_returns_0) {
  keeler::RbTree<int, int> tree;

  const auto sz = tree.size();

  EXPECT_EQ(sz, 0);
}

TEST(RbTree, tree_insert_single_element_size_returns_1) {
  keeler::RbTree<int, int> tree;

  tree.insert({1, 2});
  const auto sz = tree.size();

  EXPECT_EQ(sz, 1);
}
