#ifndef CHP23_H
#define CHP23_H

#include "chp21.h"
#include <algorithm>
#include <iterator>
#include <queue>
#include <vector>

class Graph
{
  public:
    class Vertex;

    struct Edge
    {
        const Vertex* source;
        const Vertex* target;
        int weight;
    };

    class Vertex
    {
      public:
        Vertex(int id);

        int Id() const
        {
            return _id;
        }

        friend inline bool operator==(const Vertex& lhs, const Vertex& rhs)
        {
            return lhs._id == rhs._id;
        }

      private:
        friend class Graph;
        int _id;
        std::vector<Edge> _edges;
    };

    using vertex_iterator = std::vector<Vertex>::iterator;
    using const_vertex_iterator = std::vector<Vertex>::const_iterator;

    using edge_iterator = std::vector<Edge>::iterator;
    using const_edge_iterator = std::vector<Edge>::const_iterator;

    Vertex AddVertex();
    void AddEdge(const Vertex& u, const Vertex& v, int weight);

    vertex_iterator begin();
    vertex_iterator end();

    const_vertex_iterator cbegin() const;
    const_vertex_iterator cend() const;

    edge_iterator edges_begin();
    edge_iterator edges_end();

    const_edge_iterator edges_cbegin() const;
    const_edge_iterator edges_cend() const;

  private:
    std::vector<Vertex> _vertices;
    std::vector<Edge> _edges;
};

template<typename T>
void KruskalsMST(Graph& g, std::back_insert_iterator<T> bii)
{
    DisjointSets ds;
    for (const auto& v : g)
    {
        ds.MakeSet(v.Id());
    }

    auto cmp = [](const Graph::Edge& lhs, const Graph::Edge& rhs) {
        return lhs.weight > rhs.weight;
    };

    std::priority_queue<Graph::Edge, std::vector<Graph::Edge>, decltype(cmp)>
        sortedEdges(g.edges_cbegin(), g.edges_cend(), cmp);

    while (!sortedEdges.empty())
    {
        auto& edge = sortedEdges.top();

        const auto set1 = ds.FindSet(edge.source->Id());
        const auto set2 = ds.FindSet(edge.target->Id());

        if (set1 != set2)
        {
            ds.Union(set1, set2);
            bii = edge;
        }

        sortedEdges.pop();
    }
}

#endif  //CHP23_H
