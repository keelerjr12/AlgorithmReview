#include <gtest/gtest.h>
#include "chp10.h"

TEST(LinkedList, empty_list_returns_empty) {
    
  keeler::List<int> list;

  auto act_val = list.empty();
  EXPECT_TRUE(act_val);
}

TEST(LinkedList, non_empty_list_returns_non_empty) {
    
  keeler::List<int> list;

  list.push_back(1);

  auto act_val = list.empty();
  EXPECT_FALSE(act_val);
}

TEST(LinkedList, empty_list_size_returns_zero) {
    
  const auto SIZE_EXPECTED = 0;
  keeler::List<int> list;

  auto sz = list.size();
  EXPECT_EQ(SIZE_EXPECTED, sz);
}

TEST(LinkedList, list_size_one_returns_one) {
    
  const auto SIZE_EXPECTED = 1;
  keeler::List<int> list;

  list.push_back(1);

  auto sz = list.size();
  EXPECT_EQ(SIZE_EXPECTED, sz);
}

TEST(LinkedList, list_size_more_than_one_returns_more_than_one) {
    
  const auto SIZE_EXPECTED = 2;
  keeler::List<int> list;

  list.push_back(1);
  list.push_back(2);
  list.pop_back();
  list.push_back(2);

  auto sz = list.size();
  EXPECT_EQ(SIZE_EXPECTED, sz);
}


TEST(LinkedList, push_single_value_front_returns_value) {
    
  const int EXP_VAL = 1;
  keeler::List<int> list;

  list.push_back(EXP_VAL);
  auto act_val = list.front();

  EXPECT_EQ(act_val, EXP_VAL);
}

TEST(LinkedList, push_multiple_values_front_returns_head) {
    
  const int EXP_VAL = 1;
  keeler::List<int> list;

  list.push_back(EXP_VAL);
  list.push_back(EXP_VAL + 1);
  auto act_val = list.front();

  EXPECT_EQ(act_val, EXP_VAL);
}

TEST(LinkedList, push_single_value_back_returns_value) {
    
  const int EXP_VAL = 1;
  keeler::List<int> list;

  list.push_back(EXP_VAL);
  auto act_val = list.back();

  EXPECT_EQ(act_val, EXP_VAL);
}

TEST(LinkedList, push_multiple_values_back_returns_tail) {
    
  const int EXP_VAL = 1;
  keeler::List<int> list;

  list.push_back(EXP_VAL - 1);
  list.push_back(EXP_VAL);
  auto act_val = list.back();

  EXPECT_EQ(act_val, EXP_VAL);
}

TEST(LinkedList, push_single_value_pop_back_empty) {
    
  const int EXP_VAL = 1;
  keeler::List<int> list;

  list.push_back(EXP_VAL);
  list.pop_back();
  auto act_val = list.empty();

  EXPECT_TRUE(act_val);
}

TEST(LinkedList, push_multiple_values_pop_back_back_returns_new_tail) {
    
  const int EXP_VAL = 1;
  keeler::List<int> list;

  list.push_back(EXP_VAL);
  list.push_back(EXP_VAL + 1);
  list.pop_back();
  auto act_val = list.back();

  EXPECT_EQ(act_val, EXP_VAL);
}

TEST(LinkedList, push_multiple_values_clear_returns_empty) {
    
  const int INIT_VAL = 1;
  keeler::List<int> list;

  list.push_back(INIT_VAL);
  list.push_back(INIT_VAL);
  list.clear();
  auto act_val = list.empty();

  EXPECT_TRUE(act_val);
}