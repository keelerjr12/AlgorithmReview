#include <gtest/gtest.h>
#include "chp10.h"

TEST(Vector, empty_vector_empty_returns_true) {
  keeler::Vector<int> vec;

  auto act_val = vec.empty();

  EXPECT_TRUE(act_val);
}

TEST(Vector, nonempty_vector_empty_returns_false) {
  keeler::Vector<int> vec;
  vec.push_back(1);

  auto act_val = vec.empty();

  EXPECT_FALSE(act_val);
}

TEST(Vector, empty_vector_capacity_returns_zero) {
  const int EXP_CAPACITY = 0;
  keeler::Vector<int> vec;

  auto act_capacity = vec.capacity();

  EXPECT_EQ(EXP_CAPACITY, act_capacity);
}

TEST(Vector, vector_one_element_capacity_returns_one_element) {
  const int EXP_CAPACITY = 1;
  keeler::Vector<int> vec;
  vec.push_back(1);

  auto act_capacity = vec.capacity();

  EXPECT_EQ(EXP_CAPACITY, act_capacity);
}

TEST(Vector, empty_vector_pushback_single_element_returns_single_element) {
  const int EXP_VALUE = 159;
  keeler::Vector<int> vec;
  vec.push_back(EXP_VALUE);

  const auto val = vec[0];

  EXPECT_EQ(EXP_VALUE, val);
}