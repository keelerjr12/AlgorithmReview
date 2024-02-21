#include "chp23.h"

UGraph::Vertex::Vertex(int id)
  : _id(id)
{}

int UGraph::Vertex::Id() const
{
    return _id;
}

UGraph::Vertex UGraph::AddVertex()
{
    const auto n = _vertices.size();
    const UGraph::Vertex v(n);

    _vertices.push_back(v);

    return v;
}

void UGraph::AddEdge(const Vertex& u, const Vertex& v, int weight)
{
    _edges.push_back({&u, &v, weight});
    _edges.push_back({&v, &u, weight});
}

std::span<const UGraph::Vertex> UGraph::Vertices() const
{
    return _vertices;
}

std::span<const UGraph::Edge> UGraph::Edges() const
{
    return _edges;
}

std::vector<UGraph::Edge> UGraph::Edges(const UGraph::Vertex& v) const
{
    std::vector<Edge> out;

    std::copy_if(_edges.begin(),
                 _edges.end(),
                 std::back_inserter(out),
                 [&](const Edge& edge) {
                     return edge.source->Id() == v.Id();
                 });

    return out;
}
