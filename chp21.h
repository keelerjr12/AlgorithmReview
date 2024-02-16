#ifndef CHP21_H
#define CHP21_H

#include <vector>

/* struct Set;

struct Element {
    int val;
    Set* parent;
    Element* next;
};

struct Set {
    Element* head = nullptr;
    Element* tail = nullptr;
};

void MakeSet(int x);

Set& FindSet(int x);

void Union(int x, int y); */

class DisjointSets
{
  public:
    DisjointSets();

    void MakeSet(int x);

    int FindSet(int x);

    void Union(int x, int y);

  private:

    std::vector<int> parent;
};

#endif  //CHP21_H
