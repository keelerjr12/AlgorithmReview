#include <gtest/gtest.h>
#include "chp10.h"

TEST(Vector, vector_one_element_front_returns_first_element) {
  const auto EXP_VAL = 3;
  keeler::Vector<int> vec;
  vec.push_back(EXP_VAL);

  const auto act_val = vec.front();

  EXPECT_EQ(EXP_VAL, act_val);
}

TEST(Vector, vector_one_element_front_modifies_first_element) {
  const auto INIT_VAL = 5;
  const auto EXP_VAL = 3;
  keeler::Vector<int> vec;
  vec.push_back(INIT_VAL);

  vec.front() = EXP_VAL;
  const auto act_val = vec.front();

  EXPECT_EQ(EXP_VAL, act_val);
}

TEST(Vector, vector_multiple_elements_front_returns_first_element) {
  const auto EXP_VAL = 3;
  keeler::Vector<int> vec;
  vec.push_back(EXP_VAL);
  vec.push_back(EXP_VAL + 1);

  const auto act_val = vec.front();

  EXPECT_EQ(EXP_VAL, act_val);
}

TEST(Vector, vector_one_element_back_returns_last_element) {
  const auto EXP_VAL = 3;
  keeler::Vector<int> vec;
  vec.push_back(EXP_VAL);

  const auto act_val = vec.back();

  EXPECT_EQ(EXP_VAL, act_val);
}

TEST(Vector, vector_one_element_back_modifies_last_element) {
  const auto INIT_VAL = 5;
  const auto EXP_VAL = 3;
  keeler::Vector<int> vec;
  vec.push_back(INIT_VAL);

  vec.back() = EXP_VAL;
  const auto act_val = vec.back();

  EXPECT_EQ(EXP_VAL, act_val);
}

TEST(Vector, vector_multiple_elements_back_returns_last_element) {
  const auto EXP_VAL = 3;
  keeler::Vector<int> vec;
  vec.push_back(EXP_VAL + 1);
  vec.push_back(EXP_VAL);

  const auto act_val = vec.back();

  EXPECT_EQ(EXP_VAL, act_val);
}

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