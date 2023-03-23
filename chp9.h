#ifndef CHP9_H
#define CHP9_H

#include "chp2.h"
#include "chp7.h"
#include "utility.h"

namespace keeler {

    template<typename ForwardIt>
    ForwardIt min_element(ForwardIt first, ForwardIt last) {
        auto min_el = first;

        for (; first != last; ++first) {
            if (*first < *min_el) {
                min_el = first;
            }
        }

        return min_el;
    }

    template <typename RandomIt>
    void nth_element(RandomIt first, RandomIt nth, RandomIt last) {
        while (first < last) {
            auto q = randomized_partition(first, last);

            if (q == nth) {
                return;
            }
            
            auto num_el_to_n = std::distance(first, nth);
            auto num_el_to_q = std::distance(first, q);

            if (num_el_to_q > num_el_to_n) {
                last = q;
            } else {
                first = std::next(q);
            }
        } 
    }

}

#endif // CHP9_H