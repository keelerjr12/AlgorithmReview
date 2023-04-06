#include <algorithm>
#include <iostream>
#include <vector>
#include "chp10.h"
#include "utility.h"
#include <list>

int main() {
    keeler::Vector<int> v;
    v.push_back(1);

    std::vector<int> a(16);

    for (auto i = 0; i < a.size(); ++i)
      std::cout << a[i] << std::endl;

    return 0;
}
