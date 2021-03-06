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

TEST(Strings, FreqAlphabets)
{
    CHECK_EQUAL("jkab", freqAlphabets("10#11#12"));
    CHECK_EQUAL("acz", freqAlphabets("1326#"));
    CHECK_EQUAL("y", freqAlphabets("25#"));
    CHECK_EQUAL("abcdefghijklmnopqrstuvwxyz", freqAlphabets("12345678910#11#12#13#14#15#16#17#18#19#20#21#22#23#24#25#26#"));
}

TEST(Strings, HalvesAreAlike)
{
    CHECK(halvesAreAlike("book"));
    CHECK(!halvesAreAlike("textbook"));
    CHECK(!halvesAreAlike("MerryChristmas"));
    CHECK(halvesAreAlike("AbCdefGh"));
}

TEST(Strings, TitleToNumber)
{
    CHECK_EQUAL(1, titleToNumber("A"));
    CHECK_EQUAL(26, titleToNumber("Z"));
    CHECK_EQUAL(28, titleToNumber("AB"));
    CHECK_EQUAL(701, titleToNumber("ZY"));
    CHECK_EQUAL(2147483647, titleToNumber("FXSHRXW"));
}

TEST(Strings, CommonChars)
{
    std::vector<std::string> arr = {"bella","label","roller"};
    std::vector<std::string> expected = {"e","l","l"};
    std::vector<std::string> result = commonChars(arr);
    CHECK_EQUAL(expected.size(), result.size());
    for (size_t i = 0; i < result.size(); ++i)
    {
        CHECK_EQUAL(expected[i], result[i]);
    }

    arr = {"cool","lock","cook"};
    expected = {"c", "o"};
    result = commonChars(arr);
    CHECK_EQUAL(expected.size(), result.size());
    for (size_t i = 0; i < result.size(); ++i)
    {
        CHECK_EQUAL(expected[i], result[i]);
    }
}

TEST(Strings, AreAlmostEqual)
{
    CHECK(areAlmostEqual("bank", "kanb"));
    CHECK(!areAlmostEqual("attack", "defend"));
    CHECK(areAlmostEqual("kelb", "kelb"));
    CHECK(!areAlmostEqual("abcd", "dcba"));
}

TEST(Strings, Interpret)
{
    CHECK_EQUAL("Goal", interpret("G()(al)"));
    CHECK_EQUAL("Gooooal", interpret("G()()()()(al)"));
    CHECK_EQUAL("alGalooG", interpret("(al)G(al)()()G"));
}

TEST(Strings, ToGoatLatin)
{
    CHECK_EQUAL("Imaa peaksmaaa oatGmaaaa atinLmaaaaa", toGoatLatin("I speak Goat Latin"));
}

TEST(Strings, GenerateTheString)
{
    CHECK_EQUAL("x", generateTheString(1));
    CHECK_EQUAL("xy", generateTheString(2));
    CHECK_EQUAL("xxx", generateTheString(3));
    CHECK_EQUAL("xxxy", generateTheString(4));
}

TEST(Strings, FindTheDifference)
{
    CHECK_EQUAL('e', findTheDifference("abcd", "abcde"));
    CHECK_EQUAL('y', findTheDifference("", "y"));
    CHECK_EQUAL('a', findTheDifference("a", "aa"));  
    CHECK_EQUAL('a', findTheDifference("ae", "aea"));  
}


TEST(Strings, CountCharacters)
{
    std::vector<std::string> words = { "cat","bt","hat","tree" };
    std::string chars = "atach";
    CHECK_EQUAL(6, countCharacters(words, chars));

    words = { "hello","world","leetcode" };
    chars = "welldonehoneyr";
    CHECK_EQUAL(10, countCharacters(words, chars));
}

TEST(Strings, SortString)
{
    // CHECK_EQUAL("abccbaabccba", sortString("aaaabbbbcccc"));
}

TEST(Strings, GcdOfStrings)
{
//    CHECK_EQUAL("ABC", gcdOfStrings("ABCABC", "ABC"));
}

TEST(Strings, IsIsomorphic)
{
    CHECK(isIsomorphic("egg", "add"));
    CHECK(!isIsomorphic("foo", "bar"));
    CHECK(isIsomorphic("paper", "title"));
    CHECK(!isIsomorphic("bbbaaaba", "aaabbbba"));
    CHECK(!isIsomorphic("aabbaa", "ccddee"));
}

TEST(Strings, FindWords)
{
    std::vector<std::string> words = {"Hello","Alaska","Dad","Peace"};
    std::vector<std::string> expected = {"Alaska","Dad"};
    std::vector<std::string> result = findWords(words);
    CHECK_EQUAL(expected.size(), result.size());
    for (size_t i = 0; i < expected.size(); ++i)
    {
        CHECK_EQUAL(expected[i], result[i]);
    }

    words = {"omk"};
    expected = {};
    result = findWords(words);
    CHECK_EQUAL(expected.size(), result.size());
    for (size_t i = 0; i < expected.size(); ++i)
    {
        CHECK_EQUAL(expected[i], result[i]);
    }

    words = {"adsdf","SFD"};
    expected = {"adsdf","SFD"};
    result = findWords(words);
    CHECK_EQUAL(expected.size(), result.size());
    for (size_t i = 0; i < expected.size(); ++i)
    {
        CHECK_EQUAL(expected[i], result[i]);
    }
}

TEST(Strings, BalancedStringSplit)
{
    CHECK_EQUAL(4, balancedStringSplit("RLRRLLRLRL"));
    CHECK_EQUAL(3, balancedStringSplit("RLLLLRRRLR"));
    CHECK_EQUAL(1, balancedStringSplit("LLLLRRRR"));
    CHECK_EQUAL(2, balancedStringSplit("RLRRRLLRLL"));
}

TEST(Strings, ToLowercase)
{
    CHECK_EQUAL("hello", toLowerCase("Hello"));
    CHECK_EQUAL("here", toLowerCase("here"));
}

TEST(Strings, RemoveOuterParentheses)
{
    CHECK_EQUAL("()()()", removeOuterParentheses("(()())(())"));
    // CHECK_EQUAL("()()()()(())", removeOuterParentheses("(()())(())(()(()))"));
}

TEST(Strings, TruncateSentence)
{
    CHECK_EQUAL("Hello how are you", truncateSentence("Hello how are you Contestant", 4));
    CHECK_EQUAL("What is the solution", truncateSentence("What is the solution to this problem", 4))
    CHECK_EQUAL("chopper is not a tanuki", truncateSentence("chopper is not a tanuki", 5));
}

TEST(Strings, UniqueMorseRepresentations)
{
    std::vector<std::string> words = {"gin", "zen", "gig", "msg"};
    CHECK_EQUAL(2, uniqueMorseRepresentations(words));

    words = {"gin", "zen", "gig", "msg"};
    CHECK_EQUAL(2, uniqueMorseRepresentations(words));
}

TEST(Strings, SquareIsWhite)
{
    CHECK(!squareIsWhite("a1"));
    CHECK(squareIsWhite("h3"));
    CHECK(!squareIsWhite("c7"));
    CHECK(!squareIsWhite("b2"));
}

TEST(Strings, MergeAlternately)
{
    CHECK_EQUAL("apbqcr", mergeAlternately("abc", "pqr"));
    CHECK_EQUAL("apbqrs", mergeAlternately("ab", "pqrs"));
    CHECK_EQUAL("apbqcd", mergeAlternately("abcd", "pq"));
}

TEST(Strings, JudgeCircle)
{
    CHECK(judgeCircle("UD"));
    CHECK(!judgeCircle("LL"));
    CHECK(!judgeCircle("RRDD"));
    CHECK(!judgeCircle("LDRRLRUULR"));
    CHECK(judgeCircle("RLUURDDDLU"));
}

TEST(Strings, ReverseWordsII)
{
    CHECK_EQUAL("s'teL ekat edoCteeL tsetnoc", reverseWords("Let's take LeetCode contest"));
    CHECK_EQUAL("doG gniD", reverseWords("God Ding"));
}

TEST(Strings, ShortestToChar)
{
    std::vector<int> expected = { 3,2,1,0,1,0,0,1,2,2,1,0 };
    std::vector<int> result = shortestToChar("loveleetcode", 'e');
    for (int i = 0; i < result.size(); ++i)
    {
        CHECK_EQUAL(expected[i], result[i]);
    }

    expected = { 3,2,1,0 };
    result = shortestToChar("aaab", 'b');
    for (int i = 0; i < result.size(); ++i)
    {
        CHECK_EQUAL(expected[i], result[i]);
    }
    
    expected = { 2,1,0,1 };
    result = shortestToChar("aaba", 'b');
    for (int i = 0; i < result.size(); ++i)
    {
        CHECK_EQUAL(expected[i], result[i]);
    }

    expected = { 1,0,0,1 };
    result = shortestToChar("abba", 'b');
    for (int i = 0; i < result.size(); ++i)
    {
        CHECK_EQUAL(expected[i], result[i]);
    }
}


TEST(Strings, NumUniqueEmails)
{
    std::vector<std::string> emails = 
        {
            "test.email+alex@leetcode.com",
            "test.e.mail+bob.cathy@leetcode.com",
            "testemail+david@lee.tcode.com"
        };

    CHECK_EQUAL(2, numUniqueEmails(emails));
    
    emails = 
        {
            "a@leetcode.com",
            "b@leetcode.com",
            "c@leetcode.com"
        };

    CHECK_EQUAL(3, numUniqueEmails(emails));
}

TEST(Strings, RemoveDuplicates)
{
    CHECK_EQUAL("ca", removeDuplicates("abbaca"));
    CHECK_EQUAL("a", removeDuplicates("aaaaaaaaa"));
}

TEST(Strings, CheckIfPangram)
{
    CHECK(checkIfPangram("thequickbrownfoxjumpsoverthelazydog"));
    CHECK(!checkIfPangram("leetcode"));
}

TEST(Strings, CanConstruct)
{
    CHECK(!canConstruct("a", "b"));
    CHECK(!canConstruct("aa", "ab"));
    CHECK(canConstruct("aa", "aab"));
}

TEST(Strings, MaxNumberOfBalloons)
{
    CHECK_EQUAL(1, maxNumberOfBalloons("nlaebolko"));
    CHECK_EQUAL(2, maxNumberOfBalloons("loonbalxballpoon"));
    CHECK_EQUAL(0, maxNumberOfBalloons("leetcode"));
}

TEST(Strings, MaxLengthBetweenEqualCharacters)
{
    CHECK_EQUAL(0, maxLengthBetweenEqualCharacters("aa"));
    CHECK_EQUAL(2, maxLengthBetweenEqualCharacters("abca"));
    CHECK_EQUAL(-1, maxLengthBetweenEqualCharacters("cbzxy"));
    CHECK_EQUAL(4, maxLengthBetweenEqualCharacters("cabbac"));
}

TEST(Strings, ReplaceDigits)
{
    CHECK_EQUAL("abcdef", replaceDigits("a1c1e1"));
    CHECK_EQUAL("abbdcfdhe", replaceDigits("a1b2c3d4e"));
}

TEST(Strings, MostCommonWord)
{
    std::string paragraph = "Bob hit a ball, the hit BALL flew far after it was hit.";
    std::vector<std::string> banned = {"hit"};
    CHECK_EQUAL("ball", mostCommonWord(paragraph, banned));

    paragraph = "a.";
    banned = {""};
    CHECK_EQUAL("a", mostCommonWord(paragraph, banned));

    paragraph = "K; P; u, M' o. W! S; y? y, k, T' t; M, E, N? Q! J, w' x. s; S. Y. R; V, P? U; P? o; g? W, N; N' S, W, h, Z' T? t! l' T? x! K; o. F? q. w? Q, s? Q! m; g? x? R; L' q, C; f! E? x? T; f, r! O. K! P, x. z; l' j. Y, S! w? w, j. U; s, M? r' J? Z. x; T. z; Q; Q? J' w' W, p! V, P; t! x? o; G' z' u, V, C' S; O? I; g, r. C? y. t! O, t' n. y. Q. N? L. t; I, X' W; w! M; m? Y? f? Z. s? x? U. q! I, i, v! p, V! Z; z; F! D. R, r' y. r' v. j! Y, M! U. M, p; Y, u' P, t, R. w? S! W. X. U? R? X' s, e. w' V; I' Y; z? l! s, u! z! R' a; R' y' S' Q? l, j, L; W. V! w; V, y? R! h. V. L, Y. X, Y' Q? U; y, n! V, y? N; V; x' H' U? K; O! X! d. U, W' U' x. Y; L' X, T? t, V, L; r! k! u' N. y; P. S, e! j, X! t' Z; s? y! u; n' K, T, Z. w. l! Y; g' x, H; U' D! Y? e, b, W. X! u; W; v, S. Z, y? o? K, P? Q? Z, Y' P; n. V? h; J, v! v; X; V. s. y. g' m? l, X. K! u? O? j; u, n' T. O' S; W. U; m. G! Z! Z, K, v. q. Z? q; Z; o? P? I. X, z! t! w' v. z! N' o! M' Z' Z? V. S; Q. O; Z! k. X! r! w. T! q. M? n, I, M; R, d, h; Z, z' n,";
    banned = {"n","q","l","i","u","d","h","o","y","b","c","t","v","a","x","m","k","w","s","z"};
    CHECK_EQUAL("r", mostCommonWord(paragraph, banned));
}

TEST(Strings, ReverseOnlyLetters)
{
    CHECK_EQUAL("dc-ba", reverseOnlyLetters("ab-cd"));
    CHECK_EQUAL("j-Ih-gfE-dCba", reverseOnlyLetters("a-bC-dEf-ghIj"));
    CHECK_EQUAL("Qedo1ct-eeLg=ntse-T!", reverseOnlyLetters("Test1ng-Leet=code-Q!"));
}

TEST(Strings, GroupAnagrams)
{
    std::vector<std::string> strs = {"eat","tea","tan","ate","nat","bat"};
    std::vector<std::vector<std::string>> expected =
        {{"bat"},{"tan", "nat"},{"eat","tea", "ate"}};

    auto result = groupAnagrams(strs);
    CHECK_EQUAL(expected.size(), result.size());
    for (size_t i = 0; i < expected.size(); ++i)
    {
        CHECK_EQUAL(expected[i].size(), result[i].size());
        for (size_t j = 0; j < expected[i].size(); ++j)
        {
            CHECK_EQUAL(expected[i][j], result[i][j]);
        }
    }

    strs = {""};
    expected =
        {{""}};

    result = groupAnagrams(strs);
    CHECK_EQUAL(expected.size(), result.size());
    for (size_t i = 0; i < expected.size(); ++i)
    {
        CHECK_EQUAL(expected[i].size(), result[i].size());
        for (size_t j = 0; j < expected[i].size(); ++j)
        {
            CHECK_EQUAL(expected[i][j], result[i][j]);
        }
    }

    strs = {"a"};
    expected =
        {{"a"}};

    result = groupAnagrams(strs);
    CHECK_EQUAL(expected.size(), result.size());
    for (size_t i = 0; i < expected.size(); ++i)
    {
        CHECK_EQUAL(expected[i].size(), result[i].size());
        for (size_t j = 0; j < expected[i].size(); ++j)
        {
            CHECK_EQUAL(expected[i][j], result[i][j]);
        }
    }
}

TEST(Strings, FrequencySort)
{
    CHECK_EQUAL("eetr", frequencySort("tree"));
    CHECK_EQUAL("cccaaa", frequencySort("cccaaa"));
    CHECK_EQUAL("bbaA", frequencySort("Aabb"));
}

TEST(Strings, IntToRoman)
{
    CHECK_EQUAL("III", intToRoman(3));
    CHECK_EQUAL("IV", intToRoman(4));
    CHECK_EQUAL("IX", intToRoman(9));
    CHECK_EQUAL("LVIII", intToRoman(58));
    CHECK_EQUAL("MCMXCIV", intToRoman(1994));
}