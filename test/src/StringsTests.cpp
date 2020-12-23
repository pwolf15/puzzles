#include "CppUTest/TestHarness.h"

#include <iostream>

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
    CHECK_EQUAL("-362032", ConvertBase("-65536", 10, 7));
}

TEST(Strings, SSDecodeColID)
{
    CHECK_EQUAL(1, SSDecodeColID("A"));
    CHECK_EQUAL(27, SSDecodeColID("AA"));
    CHECK_EQUAL(4, SSDecodeColID("D"));
    CHECK_EQUAL(702, SSDecodeColID("ZZ"));
}

TEST(Strings, SSDecodeColIDBase0)
{
    // CHECK_EQUAL(0, SSDecodeColIDBase0("A"));
    // CHECK_EQUAL(26, SSDecodeColIDBase0("AA"));
    // CHECK_EQUAL(3, SSDecodeColIDBase0("D"));
    // CHECK_EQUAL(650, SSDecodeColIDBase0("ZZ"));
}

TEST(Strings, ReplaceAndRemove)
{
    {
        char str[20] = { 'a', 'b', 'a', 'c', 'b', 'c', 'a' };
        CHECK_EQUAL(5, ReplaceAndRemove(4, str));
        char exp[20] = { 'd', 'd', 'd', 'd', 'c', 'd', 'd' };
        for (int i = 0; i < 5; ++i)
        {
            CHECK_EQUAL(exp[i], str[i]);
        }
    }
    {
        char str[6] = { 'a', 'b', 'c', 'b', 'c', 'c' };
        CHECK_EQUAL(5, ReplaceAndRemove(6, str));
        char exp[5] = { 'd', 'd', 'c', 'c', 'c' };
        for (int i = 0; i < 5; ++i)
        {
            CHECK_EQUAL(exp[i], str[i]);
        }
    }  
    {
        char str[3] = { 'b', 'c', 'c' };
        CHECK_EQUAL(2, ReplaceAndRemove(3, str));
        char exp[2] = { 'c', 'c' };
        for (int i = 0; i < 2; ++i)
        {
            CHECK_EQUAL(exp[i], str[i]);
        }
    }
    {
        char str[4] = { 'b', 'c', 'c', 'a' };
        CHECK_EQUAL(4, ReplaceAndRemove(4, str));
        char exp[4] = { 'c', 'c', 'd', 'd' };
        for (int i = 0; i < 4; ++i)
        {
            CHECK_EQUAL(exp[i], str[i]);
        }
    }
    {
        char str[2] = { 'a', 'a' };
        CHECK_EQUAL(2, ReplaceAndRemove(1, str));
        char exp[2] = { 'd', 'd' };
        for (int i = 0; i < 2; ++i)
        {
            CHECK_EQUAL(exp[i], str[i]);
        }
    }
    {
        char str[1] = { 'b' };
        CHECK_EQUAL(0, ReplaceAndRemove(1, str));
    }
    {
        char str[1] = { 'c' };
        CHECK_EQUAL(1, ReplaceAndRemove(1, str));
        char exp[1] = { 'c' };
        for (int i = 0; i < 1; ++i)
        {
            CHECK_EQUAL(exp[i], str[i]);
        }
    }
    {
        char str[4] = { 'a', 'a', 'a', 'a' };
        CHECK_EQUAL(4, ReplaceAndRemove(2, str));
        char exp[4] = { 'd', 'd', 'd', 'd' };
        for (int i = 0; i < 4; ++i)
        {
            CHECK_EQUAL(exp[i], str[i]);
        }
    }
    {
        char str[2] = { 'a', 'b' };
        CHECK_EQUAL(2, ReplaceAndRemove(2, str));
        char exp[2] = { 'd', 'd' };
        for (int i = 0; i < 2; ++i)
        {
            CHECK_EQUAL(exp[i], str[i]);
        }
    }
    {
        char str[3] = { 'a', 'c' };
        CHECK_EQUAL(3, ReplaceAndRemove(2, str));
        char exp[3] = { 'd', 'd', 'c'};
        for (int i = 0; i < 3; ++i)
        {
            CHECK_EQUAL(exp[i], str[i]);
        }
    }
    {
        char str[2] = { 'b', 'a' };
        CHECK_EQUAL(2, ReplaceAndRemove(2, str));
        char exp[2] = { 'd', 'd'};
        for (int i = 0; i < 2; ++i)
        {
            CHECK_EQUAL(exp[i], str[i]);
        }
    }
    {
        char str[4] = { 'c', 'b', 'b', 'c' };
        CHECK_EQUAL(2, ReplaceAndRemove(4, str));
        char exp[2] = { 'c', 'c' };
        for (int i = 0; i < 2; ++i)
        {
            CHECK_EQUAL(exp[i], str[i]);
        }
    }
    {
        char str[4] = { 'a', 'b', 'b', 'a' };
        CHECK_EQUAL(4, ReplaceAndRemove(4, str));
        char exp[4] = { 'd', 'd', 'd', 'd' };
        for (int i = 0; i < 4; ++i)
        {
            CHECK_EQUAL(exp[i], str[i]);
        }
    }
}

TEST(Strings, IsPalindromeEPI)
{
    CHECK(IsPalindrome("racecar"));
    CHECK(IsPalindrome("A man, a plan, a canal, Panama."));
    CHECK(IsPalindrome("Able was I, ere I saw Elba!"));
    CHECK(!IsPalindrome("Ray a Ray!"));
}

TEST(Strings, ReverseWords)
{
    std::string words = "Bob likes Alice";
    ReverseWords(&words);
    CHECK_EQUAL("Alice likes Bob", words);

    words = "Alice likes Bob";
    ReverseWords(&words);
    CHECK_EQUAL("Bob likes Alice", words);

    words = "b";
    ReverseWords(&words);
    CHECK_EQUAL("b", words);

    words = "Bob";
    ReverseWords(&words);
    CHECK_EQUAL("Bob", words);

    words = "";
    ReverseWords(&words);
    CHECK_EQUAL("", words);

    words = " ";
    ReverseWords(&words);
    CHECK_EQUAL(" ", words);

    words = " Bob";
    ReverseWords(&words);
    CHECK_EQUAL("Bob ", words);

    words = " Bob ";
    ReverseWords(&words);
    CHECK_EQUAL(" Bob ", words);

    words = " Bob ";
    words = ReverseWordsLC(words);
    CHECK_EQUAL("Bob", words);
}