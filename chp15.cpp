#include "chp15.h"
#include <algorithm>
#include <limits>
#include <vector>

#include <iostream>
#include <iterator>

int naive_top_down_recursive_rod_cut(const std::vector<int>& prices, int n) {
  if (n == 0) {
    return 0;
  }

  auto max_revenue = std::numeric_limits<int>::min();

  for (auto i = 1; i <= n; ++i) {
    const auto revenue = prices[i - 1] + naive_top_down_recursive_rod_cut(prices, n - i);
    max_revenue = std::max(revenue, max_revenue);
  }

  return max_revenue;
}

int top_down_memoization_rod_cut_aux(const std::vector<int>& prices, std::vector<int>& revenues, int n) {
  if (n == 0) {
    return 0;
  }

  if (revenues[n - 1] >= 0) {
    return revenues[n - 1];
  }

  auto max_revenue = std::numeric_limits<int>::min();

  for (auto i = 1; i <= n; ++i) {
    const auto revenue = prices[i - 1] + top_down_memoization_rod_cut_aux(prices, revenues, n - i);
    max_revenue = std::max(revenue, max_revenue);
  }

  revenues[n - 1] = max_revenue;
  return max_revenue;

}

int top_down_memoization_rod_cut(const std::vector<int>& prices, int n) {
  std::vector<int> revenues(n, -1);
  return top_down_memoization_rod_cut_aux(prices, revenues, n);
}

int bottom_up_rod_cut(const std::vector<int>& prices, int n) {
  std::vector<int> revenues(n + 1, 0);

  for (auto i = 1; i <= n; ++i) {
    auto max_revenue = std::numeric_limits<int>::min();

    for (auto j = 1; j <= i; ++j) {
      auto revenue = prices[j - 1] + revenues[i - j];
      max_revenue = std::max(max_revenue, revenue);
    }

    revenues[i] = max_revenue;
  }

  return revenues[n];
}

using Matrix = std::vector<std::vector<int>>;

void print_mat(const Matrix& mat) {
  for (const auto& vec : mat) {
    std::copy(std::begin(vec), std::end(vec), std::ostream_iterator<int>(std::cout, " "));
    
    std::cout << "\n";
  }
}

Matrix solve_chain(const std::vector<int> mat_dims) {
  Matrix a(mat_dims.size() - 1, std::vector<int>(mat_dims.size() - 1, 0));
  Matrix s(mat_dims.size() - 2, std::vector<int>(mat_dims.size() - 2, 0));
  
  for (auto k = 1; k < a.size(); ++k) {
    for (auto i = 0; i < a.size() - k; ++i) {
      const auto j = k + i;

      auto min = std::numeric_limits<int>::max();
      auto s_tmp = 0;

      for (auto l = i; l < j; ++l) {
        const auto tmp = a[i][l] + a[l + 1][j] + mat_dims[i] * mat_dims[l + 1] * mat_dims[j + 1];

        if (tmp < min) {
          min = tmp;
          s_tmp = l;
        }
      }

      a[i][j] = min;
      s[i][j-1] = s_tmp;
    }
  }

  return s;
}

void print_solved_chain(const Matrix& s, int i, int j) {
  if (i == j) {
    std::cout << "A" << i;
  } else {
    std::cout << "(";

    const auto k = s[i][j - 1];

    print_solved_chain(s, i, k);
    print_solved_chain(s, k + 1, j);

    std::cout << ")";
  }
}

void print_matrix_chain_order(const std::vector<int>& mat_dims) {
  const auto s = solve_chain(mat_dims);
  print_solved_chain(s, 0, s.size());
}
