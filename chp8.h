#ifndef CHP8_H
#define CHP8_H

#include <algorithm>
#include <cmath>
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
        auto max = *std::max_element(first, last);

        for (auto divisor = 1; divisor <= std::pow(10, std::log10(max)); divisor *= 10) {
            std::array<std::vector<int>, 10> buckets;

            for (auto it = first; it < last; ++it) {
                auto index = (*it / divisor) % 10;
                buckets[index].push_back(*it);
            }

            auto out = first;
            for (const auto& bucket : buckets) {
                out = std::copy(std::begin(bucket), std::end(bucket), out);
            }
        }
    }
}

#endif // CHP8_H