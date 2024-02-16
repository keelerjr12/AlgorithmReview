#include "chp21.h"
#include <vector>

const int INIT_SZ = 2;

DisjointSets::DisjointSets()
  : parent(INIT_SZ)
  , rank(INIT_SZ)
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

    const auto x_rnk = rank[x_rep];
    const auto y_rnk = rank[y_rep];

    if (x_rnk > y_rnk)
    {
        parent[y] = x;
    }
    else if (y_rnk > x_rnk)
    {
        parent[x] = y;
    }
    else
    {
        parent[x] = y;
        ++rank[y];
    }
}
