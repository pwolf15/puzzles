#include "CppUTest/TestHarness.h"

#include "Primitives.hpp"

TEST_GROUP(Primitives)
{
 
};

TEST(Primitives, CountBits)
{
    CHECK_EQUAL(4, CountBits(15));
    CHECK_EQUAL(16, CountBits(0xAAAAAAAA));
}

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

TEST(Primitives,NumSteps)
{
    CHECK_EQUAL(6, numSteps(14));
    // magicSquare(4);
}

TEST(Primitives, CheckPerfectNumber)
{
    CHECK(checkPerfectNumber(28));
    CHECK(!checkPerfectNumber(29));
    CHECK(checkPerfectNumber(6));
    CHECK(checkPerfectNumber(496));
    CHECK(checkPerfectNumber(8128));
    CHECK(!checkPerfectNumber(2));
    CHECK(!checkPerfectNumber(1));
}

TEST(Primitives, BinaryGap)
{
    CHECK_EQUAL(2, binaryGap(22));
    CHECK_EQUAL(2, binaryGap(5));
    CHECK_EQUAL(1, binaryGap(6));
    CHECK_EQUAL(0, binaryGap(8));
    CHECK_EQUAL(0, binaryGap(1));
}

TEST(Primitives, HasAlternatingBits)
{
    CHECK(hasAlternatingBits(5));
    CHECK(!hasAlternatingBits(7));
    CHECK(!hasAlternatingBits(11));
    CHECK(hasAlternatingBits(10));
    CHECK(!hasAlternatingBits(3));
}

TEST(Primitives, ReadBinaryWatch)
{
    std::vector<std::string> expected = {"1:00", "2:00", "4:00", "8:00", "0:01", "0:02", "0:04", "0:08", "0:16", "0:32"};
    std::vector<std::string> results = readBinaryWatch(1);
    // CHECK_EQUAL(expected.size(), results.size());
    // for (size_t i = 0; i < expected.size(); ++i)
    // {
    //     CHECK_EQUAL(expected[i], results[i]);
    // }
}

TEST(Primitives, TotalMoney)
{
    CHECK_EQUAL(10, totalMoney(4));
    CHECK_EQUAL(37, totalMoney(10));
    CHECK_EQUAL(96, totalMoney(20));
}

TEST(Primitives, BitwiseComplement)
{
    CHECK_EQUAL(2, bitwiseComplement(5));
    CHECK_EQUAL(0, bitwiseComplement(7)); 
    CHECK_EQUAL(5, bitwiseComplement(10));
    CHECK_EQUAL(1, bitwiseComplement(0));
}

TEST(Primitives, GetNoZeroIntegers)
{
    std::vector<int> expected = {2, 9};
    std::vector<int> result = getNoZeroIntegers(11);
    CHECK_EQUAL(expected.size(), result.size())
    for (int i = 0; i < expected.size(); ++i)
    {
        CHECK_EQUAL(expected[i], result[i]);
    }

    expected = {1, 9999};
    result = getNoZeroIntegers(10000);
    CHECK_EQUAL(expected.size(), result.size())
    for (int i = 0; i < expected.size(); ++i)
    {
        CHECK_EQUAL(expected[i], result[i]);
    }

    expected = {1, 68};
    result = getNoZeroIntegers(69);
    CHECK_EQUAL(expected.size(), result.size())
    for (int i = 0; i < expected.size(); ++i)
    {
        CHECK_EQUAL(expected[i], result[i]);
    }

    expected = {11, 999};
    result = getNoZeroIntegers(1010);
    CHECK_EQUAL(expected.size(), result.size())
    for (int i = 0; i < expected.size(); ++i)
    {
        CHECK_EQUAL(expected[i], result[i]);
    }

    expected = {1, 1};
    result = getNoZeroIntegers(2);
    CHECK_EQUAL(expected.size(), result.size())
    for (int i = 0; i < expected.size(); ++i)
    {
        CHECK_EQUAL(expected[i], result[i]);
    }
}

TEST(Primitives, CountOdds)
{
    CHECK_EQUAL(3, countOdds(3, 7));
    CHECK_EQUAL(3, countOdds(2, 7));
    CHECK_EQUAL(4, countOdds(1, 7));
    CHECK_EQUAL(1, countOdds(8, 10));
    CHECK_EQUAL(1, countOdds(21, 22));
    CHECK_EQUAL(3, countOdds(13, 18));
}

TEST(Primitives, NumberOfMatches)
{
    CHECK_EQUAL(6, numberOfMatches(7));
    CHECK_EQUAL(13, numberOfMatches(14));
}

TEST(Primitives, DayOfTheWeek)
{
    int day = 31, month = 8, year = 2019;
    CHECK_EQUAL("Saturday", dayOfTheWeek(day, month, year));
}

TEST(Primitives, DayOfYear)
{
    CHECK_EQUAL(9, dayOfYear("2019-01-09"));
    CHECK_EQUAL(41, dayOfYear("2019-02-10"));
    CHECK_EQUAL(60, dayOfYear("2003-03-01"));
    CHECK_EQUAL(61, dayOfYear("2004-03-01"));
    CHECK_EQUAL(364, dayOfYear("1961-12-30"));
    CHECK_EQUAL(84, dayOfYear("1900-03-25"));
}

TEST(Primitives, DivisorGame)
{
    CHECK(divisorGame(2));
    CHECK(!divisorGame(3));
}

TEST(Primitives, CountLargestGroup)
{
    CHECK_EQUAL(4, countLargestGroup(13));
    CHECK_EQUAL(6, countLargestGroup(15)); 
    CHECK_EQUAL(2, countLargestGroup(2));   
    CHECK_EQUAL(5, countLargestGroup(24));  
}

TEST(Primitives, TrailingZeroes)
{
    CHECK_EQUAL(0, trailingZeroes(3));
    CHECK_EQUAL(1, trailingZeroes(5));
    CHECK_EQUAL(0, trailingZeroes(0));
    CHECK_EQUAL(0, trailingZeroes(13));
}

TEST(Primitives, Fib)
{
    CHECK_EQUAL(0, fib(0));
    CHECK_EQUAL(1, fib(1));
    CHECK_EQUAL(1, fib(2));
    CHECK_EQUAL(2, fib(3));
    CHECK_EQUAL(3, fib(4));
}

TEST(Primitives, MinPartitions)
{
    // CHECK_EQUAL(3, minPartitions("32"));
}

TEST(Primitives, GuessNumber)
{
    Guesser guesser(1);
    CHECK_EQUAL(1, guesser.guessNumber(32));
    Guesser guesser2(37);
    CHECK_EQUAL(37, guesser2.guessNumber(100));
    Guesser guesser3(6);
    CHECK_EQUAL(6, guesser3.guessNumber(10));
    Guesser guesser4(1);
    CHECK_EQUAL(1, guesser4.guessNumber(1));
    Guesser guesser5(1);
    CHECK_EQUAL(1, guesser5.guessNumber(2));
    Guesser guesser6(2);
    CHECK_EQUAL(2, guesser6.guessNumber(2));
}

TEST(Primitives, IsHappy)
{
    CHECK(isHappy(19));
    CHECK(!isHappy(2));
    CHECK(!isHappy(3));
    CHECK(isHappy(13));
}

TEST(Primitives, FindKthPositive)
{
    std::vector<int> arr = { 2, 3, 4, 7, 11 };
    CHECK_EQUAL(9, findKthPositive(arr, 5));

    arr = { 1, 2, 3, 4};
    CHECK_EQUAL(6, findKthPositive(arr, 2));
}

TEST(Primitives, XorOperation)
{
    CHECK_EQUAL(8, xorOperation(5, 0));
    CHECK_EQUAL(8, xorOperation(4, 3));
    CHECK_EQUAL(7, xorOperation(1, 7));
    CHECK_EQUAL(2, xorOperation(10, 5));
}

TEST(Primitives, SubtractProductAndSum)
{
    CHECK_EQUAL(15, subtractProductAndSum(234));
    CHECK_EQUAL(21, subtractProductAndSum(4421));
}

TEST(Primitives, Maximum69Number)
{
    CHECK_EQUAL(9969, maximum69Number(9669));
    CHECK_EQUAL(9999, maximum69Number(9999));
    CHECK_EQUAL(9999, maximum69Number(9996));
}

TEST(Primitives, NumWaterBottles)
{
    CHECK_EQUAL(13, numWaterBottles(9, 3));
    CHECK_EQUAL(19, numWaterBottles(15, 4));
    CHECK_EQUAL(6, numWaterBottles(5, 5));
    CHECK_EQUAL(2, numWaterBottles(2, 3));
}