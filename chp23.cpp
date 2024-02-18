#include "chp23.h"

Graph::Vertex::Vertex(int id)
  : _id(id)
{}

Graph::Vertex Graph::AddVertex()
{
    const auto n = _vertices.size();
    const Graph::Vertex v(n);

    _vertices.push_back(v);

    return v;
}

void Graph::AddEdge(const Vertex& u, const Vertex& v, int weight)
{
    _edges.push_back({&u, &v, weight});
    _vertices[u._id]._edges.push_back(_edges.back());

    _edges.push_back({&v, &u, weight});
    _vertices[v._id]._edges.push_back(_edges.back());
}

Graph::vertex_iterator Graph::begin()
{
    return _vertices.begin();
}

Graph::vertex_iterator Graph::end()
{
    return _vertices.end();
}

Graph::const_vertex_iterator Graph::cbegin() const
{
    return _vertices.cbegin();
}

Graph::const_vertex_iterator Graph::cend() const
{
    return _vertices.cend();
}

Graph::edge_iterator Graph::edges_begin()
{
    return _edges.begin();
}

Graph::edge_iterator Graph::edges_end()
{
    return _edges.end();
}

Graph::const_edge_iterator Graph::edges_cbegin() const
{
    return _edges.cbegin();
}

Graph::const_edge_iterator Graph::edges_cend() const
{
    return _edges.cend();
}
