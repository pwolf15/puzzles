#include "CppUTest/TestHarness.h"

#include "DynamicProgramming.hpp"

TEST_GROUP(DynamicProgramming)
{
 
};

TEST(DynamicProgramming, ClimbStairs)
{
    CHECK_EQUAL(2, climbStairs(2));
    CHECK_EQUAL(3, climbStairs(3));
    CHECK_EQUAL(1836311903, climbStairs(45));
};
