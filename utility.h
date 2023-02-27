#ifndef UTILITY_H
#define UTILITY_H

#include <iterator>

namespace Keeler {

    template<typename ForwardIt>
    void print(ForwardIt first, ForwardIt last) {
        std::copy(first, last, std::ostream_iterator<decltype(*first)>(std::cout, " "));
        std::cout << std::endl;
    }

}

#endif // UTILITY_H