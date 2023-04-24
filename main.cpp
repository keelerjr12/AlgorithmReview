#include <iostream>
#include "chp11.h"

int main() {
  keeler::UnorderedMap<int, std::string> map;
  map.insert({1, "1"});
  map.insert({3, "3"});
  map.insert({11, "11"});

  const auto bkt = 3;
  for (auto it = map.begin(bkt); it != map.end(bkt); ++it)
  {
    std::cout << "(" << it->first << ", " << it->second << "), ";
  }

  std::cout << "\n";

  return 0;
}
