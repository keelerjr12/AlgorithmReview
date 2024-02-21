#ifndef CHP23_H
#define CHP23_H

#include "chp21.h"
#include <algorithm>
#include <queue>
#include <span>
#include <unordered_set>
#include <vector>

class UGraph
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

        int Id() const;

        friend bool operator==(const Vertex& lhs, const Vertex& rhs) {
            return lhs.Id() == rhs.Id();
        }

      private:
        int _id;
    };

    Vertex AddVertex();
    void AddEdge(const Vertex& u, const Vertex& v, int weight);

    std::span<const Vertex> Vertices() const;

    std::span<const Edge> Edges() const;
    std::vector<Edge> Edges(const Vertex& v) const;

  private:
    // TODO: this will cause issues for struct Edge with reallocation
    std::vector<Vertex> _vertices;
    std::vector<Edge> _edges;
};

template<>
struct std::hash<UGraph::Vertex>
{
    std::size_t operator()(const UGraph::Vertex& v) const noexcept
    {
        const auto h = std::hash<int>{}(v.Id());
        return h;
    }
};

template<typename OutputIt>
void KruskalsMST(UGraph& g, OutputIt oi)
{
    DisjointSets ds;
    for (const auto& v : g.Vertices())
    {
        ds.MakeSet(v.Id());
    }

    auto cmp = [](const UGraph::Edge& lhs, const UGraph::Edge& rhs) {
        return lhs.weight > rhs.weight;
    };

    const auto edges = g.Edges();
    std::priority_queue<UGraph::Edge, std::vector<UGraph::Edge>, decltype(cmp)>
        sortedEdges(edges.cbegin(), edges.cend(), cmp);

    while (!sortedEdges.empty())
    {
        auto& edge = sortedEdges.top();

        const auto set1 = ds.FindSet(edge.source->Id());
        const auto set2 = ds.FindSet(edge.target->Id());

        if (set1 != set2)
        {
            ds.Union(set1, set2);
            oi = edge;
        }

        sortedEdges.pop();
    }
}

template<typename OutputIt>
void PrimsMST(UGraph& g, OutputIt oi)
{
    auto edge_cmp = [](const UGraph::Edge& lhs, const UGraph::Edge& rhs) {
        return lhs.weight > rhs.weight;
    };
    std::priority_queue<UGraph::Edge,
                        std::vector<UGraph::Edge>,
                        decltype(edge_cmp)> sortedEdges(edge_cmp);

    //start at arbitrary node
    const auto vertices = g.Vertices();
    auto vert_cmp = [](const UGraph::Vertex& u, const UGraph::Vertex& v) {
        return u.Id() < v.Id();
    };
    const auto u =
        *std::min_element(vertices.cbegin(), vertices.cend(), vert_cmp);

    //get smallest edge from node
    const auto edges = g.Edges(u);
    for (const auto& edge : edges) {
        sortedEdges.push(edge);
    }

    std::unordered_set<UGraph::Vertex> usedVerts;
    usedVerts.insert(u);
    while (usedVerts.size() != vertices.size()) {
        const auto smallestEdge = sortedEdges.top();
        sortedEdges.pop();

        const auto tgt = *smallestEdge.target;
        if (!usedVerts.contains(tgt)) {
            usedVerts.insert(tgt.Id());
            oi = smallestEdge;

            const auto edges = g.Edges(tgt);
            for (const auto& edge : edges) {
                sortedEdges.push(edge);
            }
        }
    }
}

#endif  //CHP23_H
