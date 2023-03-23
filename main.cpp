#include <algorithm>
#include <iostream>
#include <vector>
#include "chp10.h"
#include "utility.h"
#include <list>

int main() {
    const int INIT_VAL = 1;
    keeler::List<int> list;

    list.push_back(INIT_VAL + 1);
    list.push_back(INIT_VAL + 2);
    auto it = list.begin();
    auto val = *it;
    ++it;
    auto val2 = *it;

    keeler::print(std::begin(list), std::end(list));
    
    auto it1 = std::find(std::begin(list), std::end(list), 1);
    if (it1 != std::end(list)) {
      std::cout << *it1 << std::endl;
    } else {
      std::cout << "Element not found\n";
    }

    std::cout << val << std::endl;
    std::cout << val2 << std::endl;

    return 0;
}
