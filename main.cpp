#include <iostream>
#include <vector>
#include "chp8.h"
#include "utility.h"

int main() {

    std::vector<int> v1 { 3, 2, 1, 1, 5, 4, 3, 1, 4, 2, 5, 2, 1, 3 };

    Keeler::print(std::begin(v1), std::end(v1));

    Keeler::counting_sort(std::begin(v1), std::end(v1));

    Keeler::print(std::begin(v1), std::end(v1));

    return 0;
}
