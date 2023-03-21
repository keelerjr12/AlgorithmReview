#include <iostream>
#include <vector>
#include "chp10.h"
#include "utility.h"

int main() {

    const int INIT_VAL = 1;
    Keeler::List<int> list;

    list.push_back(INIT_VAL);
    list.push_back(INIT_VAL);
    list.clear();
    auto act_val = list.empty();

    std::cout << act_val << std::endl;

    return 0;
}
