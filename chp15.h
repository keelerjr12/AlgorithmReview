#ifndef CHP_15_H
#define CHP_15_H

#include <vector>

int naive_top_down_recursive_rod_cut(const std::vector<int>& prices, int n);

int top_down_memoization_rod_cut(const std::vector<int>& prices, int n);

int bottom_up_rod_cut(const std::vector<int>& prices, int n);

void print_matrix_chain_order(const std::vector<int>& mat_dims);

#endif // CHP_15_H
