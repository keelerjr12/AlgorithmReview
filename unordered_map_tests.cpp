#include <gtest/gtest.h>
#include "chp11.h"

TEST(UnorderedMap, map_empty_returns_empty_true) {
  keeler::UnorderedMap<int, int> map;

  const auto is_empty = map.empty();

  EXPECT_TRUE(is_empty);
}

TEST(UnorderedMap, map_empty_insert_single_empty__empty_false) {
  keeler::UnorderedMap<int, int> map;

  map.insert(3);
  const auto is_empty = map.empty();

  EXPECT_FALSE(is_empty);
}
