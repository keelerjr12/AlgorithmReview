#include <iostream>
#include "chp11.h"

int main() {
  keeler::UnorderedMap<int, int> map;
  map.insert(1);
  map.insert(11);
  map.insert(3);
  map.insert(2);
  map.insert(21);
  map.insert(45);
  map.insert(13);
  map.insert(35);
  map.insert(22);
  map.insert(52);

  for (auto it = map.begin(); it != map.end(); ++it)
  {
    std::cout << *it << " ";
  }

  std::cout << "\n";

  return 0;
}
