#include "chp21.h"
#include <gtest/gtest.h>

TEST(DisjointSet, Construction)
{
    const auto EXP_SIZE = 1;
    DisjointSets sets;
    sets.MakeSet(1);

    //EXPECT_EQ(EXP_REV, size);
}

TEST(DisjointSet, FindTargetElementSingleElementSet)
{
    const auto EXP_REP = 1;
    DisjointSets sets;
    sets.MakeSet(EXP_REP);

    const auto rep = sets.FindSet(EXP_REP);
    EXPECT_EQ(EXP_REP, rep);
}

TEST(DisjointSet, FindTargetElementAfterUnionTwoSets)
{
    const auto VAL1 = 1;
    const auto VAL2 = 2;
    DisjointSets sets;
    sets.MakeSet(VAL1);
    sets.MakeSet(VAL2);

    sets.Union(VAL1, VAL2);
    const auto rep1 = sets.FindSet(VAL1);
    const auto rep2 = sets.FindSet(VAL2);

    EXPECT_EQ(VAL1, rep1);
    EXPECT_EQ(VAL1, rep2);
}
