#include <iostream>
#include <vector>
#include "chp10.h"
#include "utility.h"

int main() {

    const int INIT_VAL = 1;
    Keeler::List<int> list;

    list.push_back(INIT_VAL + 1);
    list.push_back(INIT_VAL + 2);
    auto it = list.begin();
    auto val = *it;
    ++it;
    auto val2 = *it;

    std::cout << val << std::endl;
    std::cout << val2 << std::endl;

    return 0;
}
