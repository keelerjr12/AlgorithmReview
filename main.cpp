#include <iostream>
#include <vector>
#include "chp10.h"
#include "utility.h"

int main() {

//    std::vector<int> v1 { 31, 24, 1, 18, 51, 49, 32, 111, 46, 26, 55, 22, 38 };

 //   Keeler::print(std::begin(v1), std::end(v1));

    auto list = Keeler::List<int>();
    std::cout << list.empty() << std::endl;

    list.push_back(1);
    std::cout << list.front() << std::endl;
    std::cout << list.back() << std::endl;
    std::cout << list.empty() << std::endl;

    list.push_back(2);
    std::cout << list.front() << std::endl;
    std::cout << list.back() << std::endl;
    std::cout << list.empty() << std::endl;

  //  Keeler::print(std::begin(v1), std::end(v1));

    return 0;
}
