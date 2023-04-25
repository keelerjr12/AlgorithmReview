#include <iostream>
#include "chp11.h"

int main() {
  keeler::UnorderedMap<int, std::string> map;
  map.insert({1, "1"});
  map.insert({3, "3"});
  map.insert({11, "11"});

  for (const int x : {1, 2, 3}) {
    if (map.contains(x)) {
      std::cout << x << " was found\n";
    } else {
      std::cout << x << " was NOT found\n";
    }
  }

  std::cout << "\n";

  return 0;
}
