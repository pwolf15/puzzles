#include "CppUTest/TestHarness.h"

#include "Recursion.hpp"

TEST_GROUP(Recursion)
{
 
};

TEST(Recursion, Gcd)
{
    CHECK_EQUAL(12, Gcd(156, 36));
    CHECK_EQUAL(2, Gcd(22, 1000));
}