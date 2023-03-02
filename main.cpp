#include <iostream>
#include <vector>
#include "chp7.h"
#include "utility.h"

int main() {

    std::vector<int> v1 { 3, 2, 9, 7, 8, 1, 6, 4, 5};

    Keeler::print(std::begin(v1), std::end(v1));

    Keeler::quicksort(std::begin(v1), std::end(v1));

    Keeler::print(std::begin(v1), std::end(v1));

    return 0;
}
