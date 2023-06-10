#include "chp15.h"
#include <algorithm>
#include <limits>
#include <vector>

#include <iostream>
#include <iterator>

int rod_cut_td_naive(const std::vector<int>& prices, int n) {
  if (n == 0) {
    return 0;
  }

  auto max_revenue = std::numeric_limits<int>::min();

  for (auto i = 1; i <= n; ++i) {
    const auto revenue = prices[i - 1] + rod_cut_td_naive(prices, n - i);
    max_revenue = std::max(revenue, max_revenue);
  }

  return max_revenue;
}

int rod_cut_td_memoization_aux(const std::vector<int>& prices, std::vector<int>& revenues, int n) {
  if (n == 0) {
    return 0;
  }

  if (revenues[n - 1] >= 0) {
    return revenues[n - 1];
  }

  auto max_revenue = std::numeric_limits<int>::min();

  for (auto i = 1; i <= n; ++i) {
    const auto revenue = prices[i - 1] + rod_cut_td_memoization_aux(prices, revenues, n - i);
    max_revenue = std::max(revenue, max_revenue);
  }

  revenues[n - 1] = max_revenue;
  return max_revenue;

}

int rod_cut_td_memoization(const std::vector<int>& prices, int n) {
  std::vector<int> revenues(n, -1);
  return rod_cut_td_memoization_aux(prices, revenues, n);
}

int rod_cut_bu(const std::vector<int>& prices, int n) {
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

int fib_td_aux(int n, std::vector<int>& memo) {
  if (n == 0 || n == 1) {
    return n;
  } else if (memo[n] != -1) {
    return memo[n];
  }

  memo[n-1] = fib_td_aux(n - 1, memo);
  memo[n-2] = fib_td_aux(n - 2, memo);

  return memo[n-1] + memo[n-2];
}

int fib_td(int n) {
  std::vector<int> memo(n + 1, -1);
  return fib_td_aux(n, memo);
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


int top_down_matrix_chain_order_aux(int i, int j, const std::vector<int>& mat_dims, Matrix& memo) {
  if (i == j) {
    return 0;
  }
  else if (memo[i][j] != -1) {
    return memo[i][j];
  }

  auto min = std::numeric_limits<int>::max();

  for (auto k = i; k < j; ++k) {
    const auto lhs = top_down_matrix_chain_order_aux(i, k, mat_dims, memo);
    const auto rhs = top_down_matrix_chain_order_aux(k+1, j, mat_dims, memo);
    const auto work =  mat_dims[i] * mat_dims[k+1] * mat_dims[j + 1];
    const auto total = lhs + rhs + work;
    std::cout << i << " " << k << " " << j << ": " << total << std::endl;

    if (total < min) {
      min = total;
      memo[i][j] = total;
    }
  }

  return memo[i][j];
}

int top_down_matrix_chain_order(const std::vector<int>& mat_dims) {
  const auto sz = mat_dims.size() - 1;
  Matrix memo(sz, std::vector<int>(sz, -1));
  top_down_matrix_chain_order_aux(0, sz - 1, mat_dims, memo);
  print_mat(memo);
  return memo[0][sz - 1];
}
