#include "CppUTest/TestHarness.h"

#include "Strings.hpp"

TEST_GROUP(Strings)
{
 
};

TEST(Strings, FirstUniqChar)
{
    CHECK_EQUAL(0, firstUniqChar("leetcode"));
    CHECK_EQUAL(2, firstUniqChar("loveleetcode"));
};

TEST(Strings, IsAnagram)
{
    CHECK(isAnagram("anagram", "nagaram"));
    CHECK(!isAnagram("rat", "car"));
};

TEST(Strings, DetectCapitalUse)
{
    CHECK(detectCapitalUse("USA"));
    CHECK(detectCapitalUse("Google"));
    CHECK(detectCapitalUse("leetcode"));
    CHECK(!detectCapitalUse("FlaG"));
    CHECK(!detectCapitalUse("flaG"));
};

TEST(Strings, IsPalindrome)
{
    CHECK(isPalindrome(""));
    CHECK(isPalindrome("A man, a plan, a canal: Panama"));
    CHECK(!isPalindrome("race a car"));
    CHECK(!isPalindrome(",,,,,,,,,,,,acva"));
};

TEST(Strings, reverseString)
{
    std::vector<std::vector<char>> tests = {
        {'h', 'e', 'l', 'l', 'o'},
        {' '},
        {'h', 'e', 'l', 'l', 'o', '!'},
        {'a', 'b', 'c', 'd', 'e'},
        {'a', 'b', 'c', 'd', 'e', 'f'},
        {'A', ' ', 'm', 'a', 'n', ',', ' ', 'a', ' ', 'p', 'l', 'a', 'n', ',', ' ', 'a', ' ', 'c', 'a', 'n', 'a', 'l', ':', ' ', 'P', 'a', 'n', 'a', 'm', 'a'}};

    std::vector<std::vector<char>> expected = {
        {'o', 'l', 'l', 'e', 'h'},
        {' '},
        {'!', 'o', 'l', 'l', 'e', 'h'},
        {'e', 'd', 'c', 'b', 'a'},
        {'f', 'e', 'd', 'c', 'b', 'a'},
        {'a', 'm', 'a', 'n', 'a', 'P', ' ', ':', 'l', 'a', 'n', 'a', 'c', ' ', 'a', ' ', ',', 'n', 'a', 'l', 'p', ' ', 'a', ' ', ',', 'n', 'a', 'm', ' ', 'A'}};


    auto equals = [](std::vector<char> &a, std::vector<char> &b)
    {
        bool result = true;
        for (int i = 0; i < a.size(); ++i)
        {
            if (a[i] != b[i])
            {
                result = false;
                break;
            }
        }
        return result;
    };

    int i = 0;
    for (auto test : tests)
    {
        reverseString(test);
        CHECK(equals(expected[i], test));
        i++;
    };
}

TEST(Strings, AddBinary)
{
    const std::vector<std::vector<std::string>> tests = {
        {"0", "1"},
        {"11", "1"},
        {"1010", "1011"}};

    const std::vector<std::string> expected = {
        "1",
        "100",
        "10101"};

    int i = 0;
    for (auto test : tests)
    {
        auto result = addBinary(test[0], test[1]);
        CHECK(expected[i] == result);
        i++;
    };
}

TEST(Strings, IsPalindromic)
{
    CHECK(IsPalindromic(""));
    CHECK(IsPalindromic("racecar"));
    CHECK(!IsPalindromic("racec"));
    CHECK(IsPalindromic("a"));
    CHECK(IsPalindromic("aa"));
};

TEST(Strings, StringToInt)
{
    CHECK_EQUAL(0, StringToInt("0"));
    CHECK_EQUAL(1, StringToInt("1"));
    CHECK_EQUAL(314, StringToInt("314"));
    CHECK_EQUAL(-314, StringToInt("-314"));
}

TEST(Strings, IntToString)
{
    CHECK_EQUAL("0", IntToString(0));
    CHECK_EQUAL("314", IntToString(314));
}

TEST(Strings, ConvertBase)
{
    CHECK_EQUAL("1A7", ConvertBase("615", 7, 13));
    CHECK_EQUAL("615", ConvertBase("1A7", 13, 7));
    CHECK_EQUAL("65536", ConvertBase("362032", 7, 10));
    CHECK_EQUAL("362032", ConvertBase("65536", 10, 7));
}