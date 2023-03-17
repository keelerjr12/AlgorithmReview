#include <iostream>
#include <vector>
#include "chp9.h"
#include "utility.h"

int main() {

    std::vector<int> v1 { 31, 24, 1, 18, 51, 49, 32, 111, 46, 26, 55, 22, 38 };

    Keeler::print(std::begin(v1), std::end(v1));

    auto i = std::distance(std::begin(v1), std::end(v1)) / 2;
    Keeler::nth_element(std::begin(v1), std::begin(v1) + i, std::end(v1));

    std::cout << *(std::begin(v1) + i) << std::endl;

    Keeler::print(std::begin(v1), std::end(v1));

    return 0;
}
