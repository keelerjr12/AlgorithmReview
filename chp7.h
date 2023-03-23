#ifndef CHP7_H
#define CHP7_H

#include <random>

namespace keeler {

    template<typename RandomIt>
    RandomIt partition(RandomIt first, RandomIt last) {
        const auto x = *std::prev(last);
        auto i = std::prev(first);

        for (auto j = first; j < last; ++j) {
            if (*j <= x) {
                ++i;
                std::iter_swap(i, j);
            }
        }

        return i;
    }

    template <typename RandomIt>
    RandomIt randomized_partition(RandomIt first, RandomIt last) {
        std::random_device rd;
        std::mt19937 gen(rd());

        auto n = std::distance(first, last) - 1;
        std::uniform_int_distribution<> dist(0, n);

        auto idx = dist(gen);
        auto pivot = std::next(first, idx);

        std::iter_swap(pivot, std::prev(last));
        auto q = keeler::partition(first, last);

        return q;
    }

    template<typename RandomIt>
    void quicksort(RandomIt first, RandomIt last) {
        if (first < last) {
            const auto q = partition(first, last);
            quicksort(first, q);
            quicksort(q + 1, last);
        }
    }

}

#endif // CHP7_H