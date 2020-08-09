#include "CppUTest/TestHarness.h"

#include "Primitives.hpp"

TEST_GROUP(Primitives)
{
 
};

TEST(Primitives, AddDigits)
{
    CHECK_EQUAL(2, addDigits(38));
    CHECK_EQUAL(9, addDigits(314159265));
    CHECK_EQUAL(0, addDigits(0));
    CHECK_EQUAL(4, addDigits(31));
    CHECK_EQUAL(9, addDigits(54));
    CHECK_EQUAL(1, addDigits(19));
};

TEST(Primitives, HammingWeight)
{
    CHECK_EQUAL(3,  hammingWeight(0b00000000000000000000000000001011));
    CHECK_EQUAL(1,  hammingWeight(0b00000000000000000000000010000000));
    CHECK_EQUAL(31, hammingWeight(0b11111111111111111111111111111101));
};

TEST(Primitives, PowerOfThree)
{
    CHECK(isPowerOfThree(27));
    CHECK(!isPowerOfThree(0));
    CHECK(isPowerOfThree(1));
    CHECK(isPowerOfThree(9));
}

TEST(Primitives, MissingNumber)
{
    std::vector<int> nums = {0, 1, 3};
    CHECK_EQUAL(2, missingNumber(nums));
    nums = {9,6,4,2,3,5,7,0,1};
    CHECK_EQUAL(8, missingNumber(nums));
}

TEST(Primitives, CountPrimes)
{
    CHECK_EQUAL(4, countPrimes(10));
    CHECK_EQUAL(168, countPrimes(1000));
    CHECK_EQUAL(41537, countPrimes(499979));
}

TEST(Primitives, PowerOfFour)
{
    CHECK(isPowerOfFour(64));
    CHECK(!isPowerOfFour(0));
    CHECK(isPowerOfFour(1));
    CHECK(isPowerOfFour(16));
}

TEST(Primitives, MagicSquare)
{
    magicSquare(3);
    // magicSquare(4);
}
