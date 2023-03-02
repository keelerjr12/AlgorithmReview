#ifndef CHP7_H
#define CHP7_H

#include <iostream>
#include <vector>

namespace Keeler {

    template<typename ForwardIt>
    ForwardIt partition(ForwardIt first, ForwardIt last) {
        const auto x = *std::prev(last);
        auto i = std::prev(first);

        for (auto j = first; j < last; ++j) {
            if (*j <= x) {
                ++i;
                std::swap(*i, *j);
            }
        }

        return i;
    }

    template<typename ForwardIt>
    void quicksort(ForwardIt first, ForwardIt last) {
        if (first < last) {
            const auto q = partition(first, last);
            quicksort(first, q);
            quicksort(q + 1, last);
        }
    }

}

#endif // CHP7_H