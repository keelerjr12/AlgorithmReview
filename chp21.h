#ifndef CHP21_H
#define CHP21_H

#include <vector>

class DisjointSets
{
  public:
    DisjointSets();

    void MakeSet(int x);

    int FindSet(int x);

    void Union(int x, int y);

  private:
    std::vector<int> parent;
    std::vector<int> rank;
};

#endif  //CHP21_H
