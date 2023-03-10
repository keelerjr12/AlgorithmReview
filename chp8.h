#ifndef CHP8_H
#define CHP8_H

#include <algorithm>
#include <ranges>
#include <vector>

namespace Keeler {

    template<typename ForwardIt>
    void counting_sort(ForwardIt first, ForwardIt last) {

        auto max = *std::max_element(first, last);
        std::vector<int> element_cts(max + 1, 0);

        for (auto it = first; it < last; ++it) {
            ++element_cts[*it];
        }

        for (auto it = std::next(std::begin(element_cts)); it < std::end(element_cts); ++it) {
            *it += *(std::prev(it));
        }

        auto n = std::distance(first, last);
        std::vector<int> out(n, 0);

        for (auto rev_it = std::make_reverse_iterator(last); rev_it < std::make_reverse_iterator(first); ++rev_it) {
            auto index = element_cts[*rev_it];
            out[index] = *rev_it;
            --element_cts[*rev_it];
        }

        std::copy(std::begin(out), std::end(out), first);
    }

    template<typename ForwardIt>
    void radix_sort(ForwardIt first, ForwardIt last) {
    }
}

#endif // CHP8_H