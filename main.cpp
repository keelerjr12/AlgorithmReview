#include <iostream>
#include <vector>
#include "utility.h"
#include "chp6.h"

int main() {

    std::vector<int> vec = { 5, 3, 2, 1, 4};
    Heap heap(vec);

    Keeler::print(std::begin(heap.Data()), std::end(heap.Data()));

    heap.Sort();

    Keeler::print(std::begin(heap.Data()), std::end(heap.Data()));

    return 0;
}
