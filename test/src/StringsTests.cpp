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