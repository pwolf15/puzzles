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

TEST(Strings, LookAndSay)
{
    CHECK_EQUAL("1", LookAndSay(1));
    CHECK_EQUAL("11", LookAndSay(2));
    CHECK_EQUAL("21", LookAndSay(3));
    CHECK_EQUAL("1211", LookAndSay(4));
    CHECK_EQUAL("111221", LookAndSay(5));
    CHECK_EQUAL("312211", LookAndSay(6));
    CHECK_EQUAL("13112221", LookAndSay(7));
    CHECK_EQUAL("1113213211", LookAndSay(8));
}

TEST(Strings, RomanToInteger)
{
    CHECK_EQUAL(1, RomanToInteger("I"));
    CHECK_EQUAL(5, RomanToInteger("V"));
    CHECK_EQUAL(10, RomanToInteger("X"));
    CHECK_EQUAL(50, RomanToInteger("L"));
    CHECK_EQUAL(100, RomanToInteger("C"));
    CHECK_EQUAL(500, RomanToInteger("D"));
    CHECK_EQUAL(1000, RomanToInteger("M"));
    CHECK_EQUAL(59, RomanToInteger("XXXXXIIIIIIIII"));
    CHECK_EQUAL(59, RomanToInteger("LVIIII"));
    CHECK_EQUAL(59, RomanToInteger("LIX"));
}

TEST(Strings, GetValidIpAddress)
{
    std::vector<std::string> expected = 
    {
        "1.92.168.11",
        "19.2.168.11",
        "19.21.68.11",
        "19.216.8.11",
        "19.216.81.1",
        "192.1.68.11",
        "192.16.8.11",
        "192.16.81.1",
        "192.168.1.1"
    };

    auto results = GetValidIpAddress("19216811");
    size_t i = 0;
    CHECK_EQUAL(expected.size(), results.size());
    for (auto result: results)
    {;
        CHECK_EQUAL(expected[i], result);
        i++;
    }
}

TEST(Strings, SnakeString)
{
    CHECK_EQUAL("e lHloWrdlo!", SnakeString("Hello World!"));
    CHECK_EQUAL("ymstklM aei arc ofn PiW!", SnakeString("My name is Patrick Wolf!"));
}

TEST(Strings, ZigZagString)
{
}

TEST(Strings, RLE)
{
    CHECK_EQUAL("4a1b3c2a", Encode("aaaabcccaa"));
    CHECK_EQUAL("3e4f2e", Encode("eeeffffee"));
    CHECK_EQUAL("aaaabcccaa", Decode("4a1b3c2a"));
    CHECK_EQUAL("eeeffffee", Decode("3e4f2e"));
    CHECK_EQUAL("aaaaaaaaaa", Decode("10a"));
    CHECK_EQUAL("10a1b", Encode("aaaaaaaaaab"));
}

TEST(Strings, FindStr)
{
    CHECK_EQUAL(1, findStr("car", "scart"));
    CHECK_EQUAL(0, findStr("", ""));
    CHECK_EQUAL(-1, findStr("aaaa", "aaa"));
    CHECK_EQUAL(0, findStr("a", "a"));
    CHECK_EQUAL(1, findStr("abs", "cabs"));
}

TEST(Strings, LetterCasePermutation)
{
    std::string input = "a1b2";
    std::vector<std::string> expected = {"a1b2","A1b2","a1B2","A1B2"};
    std::vector<std::string> result = letterCasePermutation(input);

    CHECK_EQUAL(expected.size(), result.size());

    for (size_t i = 0; i < expected.size(); ++i)
    {
        CHECK_EQUAL(expected[i], result[i]);
    }
}

TEST(Strings, AddStrings)
{
    std::string op1 = "123";
    std::string op2 = "456";
    std::string sum = addStrings(op1, op2);
    CHECK(sum == "579");

    op1 = "789";
    op2 = "456";
    sum = addStrings(op1, op2);
    CHECK(sum == "1245");

    op1 = "99";
    op2 = "9";
    sum = addStrings(op1, op2);
    CHECK(sum == "108");
}

TEST(Strings, BuddyStrings)
{
    std::string str1 = "ab";
    std::string str2 = "ba";
    CHECK(buddyStrings(str1, str2));

    str1 = "ab";
    str2 = "ab";
    CHECK(!buddyStrings(str1, str2));

    str1 = "aa";
    str2 = "aa";
    CHECK(buddyStrings(str1, str2));

    str1 = "aaaaaaabc";
    str2 = "aaaaaaacb";
    CHECK(buddyStrings(str1, str2));

    str1 = "abac";
    str2 = "abad";
    CHECK(!buddyStrings(str1, str2));
}

TEST(Strings, ConvertToTitle)
{
    int col = 1;
    std::string expected = "A";
    std::string result = convertToTitle(col);
    CHECK_EQUAL(expected, result);

    expected = "Z";
    col = 26;
    result = convertToTitle(col);
    CHECK_EQUAL(expected, result);

    expected = "AB";
    col = 28;
    result = convertToTitle(col);
    CHECK_EQUAL(expected, result);

    expected = "ZY";
    col = 701;
    result = convertToTitle(col);
    CHECK_EQUAL(expected, result);
}

TEST(Strings, DefangIPAddr)
{
    CHECK_EQUAL("1[.]1[.]1[.]1", defangIPaddr("1.1.1.1"));
    CHECK_EQUAL("255[.]100[.]50[.]0", defangIPaddr("255.100.50.0"));
}

TEST(Strings, BackspaceCompare)
{
    CHECK(backspaceCompare("ab#c", "ad#c"));
    CHECK(backspaceCompare("ab##", "c#d#"));
    CHECK(backspaceCompare("a##c", "#a#c"));
    CHECK(!backspaceCompare("a#c", "b"));
    CHECK(backspaceCompare("y#fo##f", "y#f#o##f"));
}

TEST(Strings, ConvertToBase7)
{
    CHECK_EQUAL("202", convertToBase7(100));
    CHECK_EQUAL("-10", convertToBase7(-7));
    CHECK_EQUAL("0", convertToBase7(0));
}

TEST(Strings, ArrayStringsAreEqual)
{
    std::vector<std::string> word1 = {"ab", "c"};
    std::vector<std::string> word2 = {"a", "bc"};

    CHECK(arrayStringsAreEqual(word1, word2));

    word1 = {"a", "cb"};
    word2 = {"ab", "c"};
    CHECK(!arrayStringsAreEqual(word1, word2));

    word1 = {"abc", "d", "defg"};
    word2 = {"abcddefg"};
    CHECK(arrayStringsAreEqual(word1, word2));
}

TEST(Strings, IsPrefixOfWord)
{
    std::string sentence = "i love eating burger";
    std::string word = "burg";
    
    CHECK_EQUAL(4, isPrefixOfWord(sentence, word));
    CHECK_EQUAL(2, isPrefixOfWord("this problem is an easy problem", "pro"));
    CHECK_EQUAL(-1, isPrefixOfWord("i am tired", "you"));  
    CHECK_EQUAL(4, isPrefixOfWord("i use triple pillow", "pill")); 
    CHECK_EQUAL(-1, isPrefixOfWord("hello from the other side", "they")); 
    CHECK_EQUAL(4, isPrefixOfWord("b bu bur burg burger", "burg"));
    CHECK_EQUAL(2, isPrefixOfWord("corona dream", "d"));
}

TEST(Strings, MaxPower)
{
    CHECK_EQUAL(2, maxPower("leetcode"));
    CHECK_EQUAL(5, maxPower("abbcccddddeeeeedcba"));
    CHECK_EQUAL(5, maxPower("triplepillooooow"));
    CHECK_EQUAL(11, maxPower("hooraaaaaaaaaaay"));
    CHECK_EQUAL(1, maxPower("tourist"));
    CHECK_EQUAL(0, maxPower(""));
    CHECK_EQUAL(2, maxPower("cc"));
}

TEST(Strings, CheckOnesSegment)
{
    CHECK(!checkOnesSegment("1001"));
    CHECK(checkOnesSegment("110"));
}

TEST(Strings, ToHex)
{
    CHECK_EQUAL("ffffffff", toHex(-1));
    CHECK_EQUAL("1a", toHex(26));
    CHECK_EQUAL("1a", toHex(26));
    // CHECK_EQUAL(toHex("110"));
}

TEST(Strings, IsLongPressedName)
{
    CHECK(isLongPressedName("alex", "aaleex"));
    CHECK(!isLongPressedName("saeed", "ssaaedd"));
    CHECK(isLongPressedName("leelee", "lleeelee"));
    CHECK(isLongPressedName("laiden", "laiden"));
    CHECK(!isLongPressedName("a", "b"));
    CHECK(!isLongPressedName("alex", "aaleexa"));
    CHECK(isLongPressedName("vtkgn", "vttkgnn"));
    CHECK(!isLongPressedName("alexd", "ale"));
    CHECK(!isLongPressedName("pyplrz", "ppyypllr"));
}

TEST(Strings, CountConsistentStrings)
{
    std::string allowed = "ab";
    std::vector<std::string> words = {"ad","bd","aaab","baa","badab"};
    CHECK_EQUAL(2, countConsistentStrings(allowed, words));

    allowed = "abc";
    words = {"a","b","c","ab","ac","bc","abc"};
    CHECK_EQUAL(7, countConsistentStrings(allowed, words));

    allowed = "cad";
    words = {"cc","acd","b","ba","bac","bad","ac","d"};
    CHECK_EQUAL(4, countConsistentStrings(allowed, words));
}

