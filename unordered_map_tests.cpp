#include <gtest/gtest.h>
#include "chp11.h"

#include <utility>

TEST(UnorderedMap, map_empty_returns_empty_true) {
  keeler::UnorderedMap<int, int> map;

  const auto is_empty = map.empty();

  EXPECT_TRUE(is_empty);
}

TEST(UnorderedMap, map_empty_insert_single_element_empty_false) {
  keeler::UnorderedMap<int, int> map;

  map.insert({3, 3});
  const auto is_empty = map.empty();

  EXPECT_FALSE(is_empty);
}

TEST(UnorderedMap, map_empty_single_element_insert_false) {
  keeler::UnorderedMap<int, int> map;

  const auto stored = map.insert({3, 3});

  EXPECT_FALSE(stored);
}

TEST(UnorderedMap, map_single_element_insert_same_element_insert_true) {
  keeler::UnorderedMap<int, int> map;

  map.insert({3, 3});
  const auto stored = map.insert({3, 3});

  EXPECT_TRUE(stored);
}

TEST(UnorderedMap, map_single_element_insert_different_element_insert_false) {
  keeler::UnorderedMap<int, int> map;

  map.insert({3, 3});
  const auto stored = map.insert({2, 2});

  EXPECT_FALSE(stored);
}

TEST(UnorderedMap, map_single_element_find_different_key_returns_end) {
  keeler::UnorderedMap<int, int> map;

  map.insert({3, 3});
  auto it = map.find(2);

  EXPECT_EQ(it, map.end());
}

TEST(UnorderedMap, map_single_element_find_same_key_returns_correct_iterator) {
  keeler::UnorderedMap<int, std::string> map;

  map.insert({3, "three"});
  map.insert({2, "two"});
  auto it = map.find(3);

  EXPECT_EQ(it->second, "three");
}
