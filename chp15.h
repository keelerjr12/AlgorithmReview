#ifndef CHP_15_H
#define CHP_15_H

#include <vector>

int rod_cut_td_naive(const std::vector<int>& prices, int n);

int rod_cut_td_memoization(const std::vector<int>& prices, int n);

int rod_cut_bu(const std::vector<int>& prices, int n);

int fib_td(int n);

void print_matrix_chain_order(const std::vector<int>& mat_dims);

int top_down_matrix_chain_order(const std::vector<int>& mat_dims);

#endif // CHP_15_H
