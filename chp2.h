#ifndef CHP2_H
#define CHP2_H

#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

namespace Keeler {

    template<typename RandomIt>
    void insertion_sort(RandomIt first, RandomIt last) {
        for(auto curr = std::next(first); curr != last; ++curr) {
            auto val = *curr;
            
            using RevIt = std::reverse_iterator<RandomIt>;
            auto insertion = std::find_if_not(RevIt(curr), RevIt(first), [=](int n) { return n > val;}).base();
            
            std::move_backward(insertion, curr, std::next(curr));
            *insertion = val;
        } 
    }

    template<typename InputIter1, typename InputIter2, typename OutputIter>
    OutputIter merge(InputIter1 first1, InputIter1 last1, InputIter2 first2, InputIter2 last2, OutputIter d_first) {
        for (; first1 != last1; ++d_first) {
            if (first2 == last2) {
                return std::copy(first1, last1, d_first);
            }

            if (*first1 < *first2) {
                *d_first = *first1;
                ++first1;
            } else {
                *d_first = *first2;
                ++first2;
            }
        }

        return std::copy(first2, last2, d_first);
    }

    template<typename RandomIt>
    void sort(RandomIt first, RandomIt last) {
        if (last - first > 1) {
            auto mid = first + (last - first) / 2;
            Keeler::sort(first, mid);
            Keeler::sort(mid, last);

            std::vector<int> output;
            Keeler::merge(first, mid, mid, last, std::back_inserter(output));
            std::copy(std::begin(output), std::end(output), first);
        } 
    }


    template<typename ForwardIter, typename T>
    bool binary_search(ForwardIter first, ForwardIter last, const T& value) {
        while (first != last) {
            const auto mid = first + (last - first) / 2;
            if (*mid < value) {
                first = std::next(mid);
            } else if (*mid > value) {
                last = std::prev(mid);
            } else {
                return true;
            }
        }

        return false;
    }

}

#endif // CHP2_H