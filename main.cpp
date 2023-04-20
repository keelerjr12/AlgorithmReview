#include <iostream>
#include "chp11.h"

int main() {
  keeler::UnorderedMap<int, int> map;
  map.insert(1);

  for (auto it = map.begin(); it != map.end(); ++it)
  {
    std::cout << "test" << std::endl;
  }

  return 0;
}
