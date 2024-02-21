#include "chp23.h"
#include <gtest/gtest.h>

#include <iostream>

TEST(Graph, EmptyGraph_SingleVertexAdded_ReturnsCorrectId)
{
    const int EXP_ID = 0;
    UGraph g;

    const auto u = g.AddVertex();

    EXPECT_EQ(u.Id(), EXP_ID);
}

TEST(Graph, EmptyGraph_MultipleVerticesAdded_ReturnDifferentIds)
{
    UGraph g;

    const auto u = g.AddVertex();
    const auto v = g.AddVertex();

    EXPECT_NE(u.Id(), v.Id());
}

TEST(Kruskals, PoorTestActingAsMain)
{
    UGraph gph;

    const auto a = gph.AddVertex();
    const auto b = gph.AddVertex();
    const auto c = gph.AddVertex();
    const auto d = gph.AddVertex();
    const auto e = gph.AddVertex();
    const auto f = gph.AddVertex();
    const auto g = gph.AddVertex();

    gph.AddEdge(a, b, 5);
    gph.AddEdge(a, c, 8);
    gph.AddEdge(a, d, 12);

    gph.AddEdge(b, c, 9);
    gph.AddEdge(b, e, 7);

    gph.AddEdge(c, d, 4);
    gph.AddEdge(c, e, 4);
    gph.AddEdge(c, f, 3);

    gph.AddEdge(d, f, 7);

    gph.AddEdge(e, f, 2);
    gph.AddEdge(e, g, 5);

    gph.AddEdge(f, g, 2);

    std::vector<UGraph::Edge> edges;
    KruskalsMST(gph, std::back_inserter(edges));

    for (const auto& edge : edges)
    {
        std::cout << "(" << edge.source->Id() << ", " << edge.target->Id()
                  << ", " << edge.weight << ")\n";
    }

    std::vector<UGraph::Vertex> vertices;
}

TEST(Prims, PoorTestActingAsMain)
{
    UGraph gph;

    const auto a = gph.AddVertex();
    const auto b = gph.AddVertex();
    const auto c = gph.AddVertex();
    const auto d = gph.AddVertex();
    const auto e = gph.AddVertex();
    const auto f = gph.AddVertex();
    const auto g = gph.AddVertex();

    gph.AddEdge(a, b, 5);
    gph.AddEdge(a, c, 8);
    gph.AddEdge(a, d, 12);

    gph.AddEdge(b, c, 9);
    gph.AddEdge(b, e, 7);

    gph.AddEdge(c, d, 4);
    gph.AddEdge(c, e, 4);
    gph.AddEdge(c, f, 3);

    gph.AddEdge(d, f, 7);

    gph.AddEdge(e, f, 2);
    gph.AddEdge(e, g, 5);

    gph.AddEdge(f, g, 2);

    std::vector<UGraph::Edge> edges;
    PrimsMST(gph, std::back_inserter(edges));

    for (const auto& edge : edges)
    {
        std::cout << "(" << edge.source->Id() << ", " << edge.target->Id()
                  << ", " << edge.weight << ")\n";
    }

    std::vector<UGraph::Vertex> vertices;
}
