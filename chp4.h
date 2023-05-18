#ifndef CHP4_H
#define CHP4_H

#include <iterator>
#include <limits>
#include <tuple>

namespace keeler {

    template<typename ForwardIter>
    std::tuple<ForwardIter, ForwardIter, int> max_sum_subarray_brute_force(ForwardIter first, ForwardIter last) {

        if (first == last)
        {
            return {first, last, 0};
        }
    
        auto max_first_it = first;
        auto max_last_it = first;
        auto max_sum = *first;

        for (; first != last; ++first) {
            auto sum = 0;

            for (auto mid_it = first; mid_it != last; ++mid_it) {
                sum += *mid_it;

                if (sum > max_sum) {
                    max_sum = sum;
                    max_first_it = first;
                    max_last_it = mid_it;
                }
            }
        }

        return {max_first_it, max_last_it, max_sum};
    }

    template<typename ForwardIter>
    std::tuple<ForwardIter, int> max_sum(ForwardIter first, ForwardIter last) {

        auto max_iter = first;
        auto max_sum = std::numeric_limits<int>::min();
        auto sum = 0;

        for (; first < last; ++first) {
            sum += *first;

            if (sum >= max_sum) {
                max_sum = sum;
                max_iter = first;
            }
        }

        return {max_iter, max_sum};
    }

    template<typename ForwardIter>
    std::tuple<ForwardIter, ForwardIter, int> max_sum_crossing_subarray(ForwardIter first, ForwardIter last) {
        auto mid_iter = first + (last - first) / 2;

        auto rev_iter = std::reverse_iterator(mid_iter);
        auto [lhs_max_iter, lhs_max_sum] = max_sum(rev_iter, std::reverse_iterator(first));
        auto [rhs_max_iter, rhs_max_sum] = max_sum(mid_iter, last);

        return {lhs_max_iter.base()-1, rhs_max_iter, lhs_max_sum + rhs_max_sum};
    }

    template<typename ForwardIter>
    std::tuple<ForwardIter, ForwardIter, int> max_sum_subarray_divide_conquer(ForwardIter first, ForwardIter last) {
        if (last - first == 0) {
            return {first, last, 0};
        } else if (last - first == 1) {
            return {first, first, *first};
        }

        auto mid = first + (last - first) / 2;
        
        auto [lhs_first, lhs_last, lhs_max_sum] = max_sum_subarray_divide_conquer(first, mid);
        auto [rhs_first, rhs_last, rhs_max_sum] = max_sum_subarray_divide_conquer(mid, last);
        auto [cross_first, cross_last, cross_max_sum] = max_sum_crossing_subarray(first, last);

        if (lhs_max_sum > rhs_max_sum && lhs_max_sum > cross_max_sum) {
            return {lhs_first, lhs_last, lhs_max_sum};
        } else if (rhs_max_sum > lhs_max_sum && rhs_max_sum > cross_max_sum) {
            return {rhs_first, rhs_last, rhs_max_sum};
        } else {
            return {cross_first, cross_last, cross_max_sum};
        }
    }

    template<typename ForwardIter>
    std::tuple<ForwardIter, ForwardIter, int> max_sum_subarray_linear(ForwardIter first, ForwardIter last) {
        auto begin = first;
        auto end = last;
        auto sum = *begin;

        for (auto inner = ++begin; inner < last; ++inner) {
            sum += *inner;

            if (*inner > sum) {
                begin = inner;
                sum = *inner;
            }

            end = inner;
        }

        return {begin, end, sum};
    }

}

#endif // CHP4_H