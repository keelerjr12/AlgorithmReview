#include "chp21.h"
#include <vector>

const int INIT_SZ = 10;

DisjointSets::DisjointSets()
  : parent(INIT_SZ)
{}

void DisjointSets::MakeSet(int x)
{
    if (x > (parent.capacity() - 1))
    {
        parent.resize(x * 2);
    }

    parent[x] = x;
}

int DisjointSets::FindSet(int x)
{
    if (parent[x] != x)
    {
        parent[x] = FindSet(parent[x]);
    }

    return parent[x];
}

void DisjointSets::Union(int x, int y)
{
    auto x_rep = FindSet(x);
    auto y_rep = FindSet(y);

    parent[y] = x;
}
