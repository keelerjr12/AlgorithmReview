#include <iostream>
#include <vector>
#include "chp8.h"
#include "utility.h"

int main() {

    std::vector<int> v1 { 31, 24, 1, 18, 51, 49, 31, 111, 46, 26, 55, 22, 13, 38 };

    Keeler::print(std::begin(v1), std::end(v1));

    Keeler::radix_sort(std::begin(v1), std::end(v1));

    Keeler::print(std::begin(v1), std::end(v1));

    return 0;
}
