#include "chp21.h"
#include <gtest/gtest.h>

TEST(DisjointSet, SingleElementSet_FindSet_ReturnSameElementAsRep)
{
    const auto EXP_REP = 1;
    DisjointSets sets;
    sets.MakeSet(EXP_REP);

    const auto rep = sets.FindSet(EXP_REP);
    EXPECT_EQ(EXP_REP, rep);
}

TEST(DisjointSet, TwoDisjointSetsSameRank_SingleUnion_ReturnSameElementAsRep)
{
    const auto VAL1 = 1;
    const auto VAL2 = 2;
    DisjointSets sets;
    sets.MakeSet(VAL1);
    sets.MakeSet(VAL2);

    sets.Union(VAL1, VAL2);
    const auto rep1 = sets.FindSet(VAL1);
    const auto rep2 = sets.FindSet(VAL2);

    EXPECT_EQ(VAL2, rep1);
    EXPECT_EQ(VAL2, rep2);
}

TEST(
    DisjointSet,
    MultipleDisjointSetsDiffRank_MultipleUnions_ReturnSameHighestRankElementAsRep)
{
    const auto VAL1 = 1;
    const auto VAL2 = 2;
    const auto VAL3 = 2;
    DisjointSets sets;
    sets.MakeSet(VAL1);
    sets.MakeSet(VAL2);
    sets.MakeSet(VAL3);

    sets.Union(VAL1, VAL2);
    sets.Union(VAL2, VAL3);
    const auto rep1 = sets.FindSet(VAL1);
    const auto rep2 = sets.FindSet(VAL2);
    const auto rep3 = sets.FindSet(VAL2);

    EXPECT_EQ(VAL2, rep1);
    EXPECT_EQ(VAL2, rep2);
    EXPECT_EQ(VAL2, rep3);
}
