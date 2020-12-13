#include "Strings.hpp"

#include <unordered_map>
#include <numeric>
#include <unordered_set>
#include <iostream>
#include <algorithm>
#include <cmath>

int firstUniqueChar_brute(std::string s)
{
    // 1. remove all duplicate characters
    // 2. get first index
    std::unordered_set<char> repeatedChars;
    std::unordered_set<char> uniqueChars;

    int i = 0;
    for (auto c : s)
    {
        if (repeatedChars.find(c) != repeatedChars.end())
        {
            // repeated, continue
        }
        else if (uniqueChars.find(c) == uniqueChars.end())
        {
            // not seen yet; add to unique list
            uniqueChars.insert(c);
        }
        else if (uniqueChars.find(c) != uniqueChars.end())
        {
            // seen already; remove from unique list and to repated
            uniqueChars.erase(c);
            repeatedChars.insert(c);
        }

        i++;
    }

    int firstIndex = -1;
    i = 0;
    for (auto c : s)
    {
        if (uniqueChars.find(c) != uniqueChars.end())
        {
            firstIndex = i;
            break;
        }

        i++;
    }

    return firstIndex;
}

// Given a string, find the first non-repeating character in it and return its index.
// If it doesn't exist, return -1.
int firstUniqChar(std::string s)
{
    return firstUniqueChar_brute(s);
}

bool isAnagram(std::string s, std::string t)
{
    std::sort(s.begin(), s.end());
    std::sort(t.begin(), t.end());
    return s == t;
}

bool detectCapitalUse(std::string word)
{
    size_t i = 0;
    enum UseType
    {
        NONE,
        ALL_CAPS,
        FIRST_CAPS,
        FIRST_CAPS_ONLY,
        NO_CAPS,
        INCORRECT
    };

    UseType usage = UseType::NONE;
    if (word.empty())
    {
        return true;
    }

    if (isupper(word[0]))
    {
        usage = UseType::FIRST_CAPS;
    }
    else
    {
        usage = UseType::NO_CAPS;
    }

    if (word.size() == 1)
    {
        return true;
    }

    for (auto c : word.substr(1))
    {
        // if current is not a capital,
        //  but second capital was found
        if (!isupper(c) && usage == UseType::ALL_CAPS)
        {
            usage = UseType::INCORRECT;
            break;
        }
        else if (!isupper(c) && usage == UseType::FIRST_CAPS)
        {
            usage = UseType::FIRST_CAPS_ONLY;
        }
        else if (isupper(c) && usage == UseType::NO_CAPS)
        {
            usage = UseType::INCORRECT;
            break;
        }
        else if (isupper(c) && usage == UseType::FIRST_CAPS)
        {
            usage = UseType::ALL_CAPS;
        }
        else if (isupper(c) && usage == UseType::FIRST_CAPS_ONLY)
        {
            usage = UseType::INCORRECT;
            break;
        }
    }

    return usage != UseType::INCORRECT;
}

bool isPalindrome(std::string s)
{

    bool isPalindrome = true;
    int i = 0;
    int j = s.size() - 1;

    if (s.empty())
    {
        return true;
    }

    while (i < j)
    {
        auto c1 = std::tolower(s[i]);
        auto c2 = std::tolower(s[j]);
        if (!isalnum(c1))
        {
            i++;
            continue;
        }
        else if (!isalnum(c2))
        {
            j--;
            continue;
        }
        else if (c1 != c2)
        {
            isPalindrome = false;
            break;
        }
        else
        {
            i++;
            j--;
        }
    }

    return isPalindrome;
}

std::string sumTwo(std::string A, std::string B)
{
    // char carry  = '0';
    // char sum    = '0';
    // for (int i = 0; i < A.size() && i < B.size(); ++i)
    // {
    //     sum = carry - '0' & A[A.size() - 1 - i])
    //     char sum = A[] == B[B.size() - 1 - i] ? '0' : '1';
    //     char carry = A[A.size() - 1 - i]
    // }
    return "";
}

void reverseString(std::vector<char> &s)
{
    // std::reverse(s.begin(), s.end());

    for (int i = 0; i < s.size() / 2; ++i)
    {
        auto temp = s[i];
        s[i] = s[s.size() - i - 1];
        s[s.size() - i - 1] = temp;
    }

    for (auto c : s)
    {
        std::cout << c << std::endl;
    }
}

std::string addBinary(std::string a, std::string b)
{

    std::string result;
    int carryIn = 0;
    int carryOut = 0;
    size_t i = 0;

    // zero-pad
    if (a.size() < b.size())
    {
        std::string zeros = std::string(b.size() - a.size(), '0');
        a = zeros + a;
    }
    else if (b.size() < a.size())
    {
        std::string zeros = std::string(a.size() - b.size(), '0');
        b = zeros + b;
    }

    while (true)
    {
        if (i >= a.size())
        {
            if (carryIn)
            {
                result += std::to_string(carryIn)[0];
            }

            break;
        }

        const auto pos = a.size() - 1 - i;
        
        // convert values to int
        int aVal = static_cast<int>(a[pos] - '0');
        int bVal = static_cast<int>(b[pos] - '0');
        
        // perform full add
        int sum = carryIn ^ (aVal ^ bVal);
        carryOut = (aVal & bVal) | (aVal & carryIn) | (bVal & carryIn);
        result += sum + '0';
        i++;
        carryIn = carryOut;
    }

    // digits currently ordered lsb -> msb
    std::reverse(result.begin(), result.end());
    return result;
}

// space complexity: O(1)
// time complexity: O(N)
bool IsPalindromic_PW(const std::string& s)
{
    for (int i = 0; i < s.size() / 2; ++i)
    {
        if (s[i] != s[s.size() - 1 - i])
        {
            return false;
        }
    }

    return true;
}

// space complexity: O(1)
// time complexity: O(N)
bool IsPalindromic_EPI(const std::string& s)
{
    for (int i = 0, j = s.size() - 1; i < j; ++i, --j)
    {
        if (s[i] != s[j])
        {
            return false;
        }
    }
    return true;
}

// space complexity: O(1)
// time complexity: O(N)
bool IsPalindromic(const std::string& s)
{
    return IsPalindromic_PW(s);
}

// time complexity: O(N)
// space complexity: O(1)
int StringToInt_PW(const std::string& s)
{
    if (s.empty())
    {
        return 0;
    }

    int sign            = s[0] == '-' ? -1 : 1;
    int total           = 0;
    int start_offset    = s.size() - 1;
    int end_offset      = sign == -1 ? 1 : 0;
    for (int i = start_offset; i >= end_offset; i--)
    {
        int dig = s[i] - '0';
        total += pow(10, start_offset - i) * dig;
    }

    return total * sign;
}

// time complexity: O(N)
// space complexity: O(1)
int StringToInt_EPI(const std::string& s)
{
    return (s[0] == '-' ? -1 : 1) * std::accumulate(std::begin(s) + (s[0] == '-'), std::end(s), 0, [](int running_sum, char c) {
        return running_sum * 10 + c - '0';
    });
}

int StringToInt(const std::string& s)
{
    return StringToInt_EPI(s);
}

// time complexity: O(2*N)
// space complexity: O(1)
std::string IntToString_PW(int i)
{
    std::string result = "";
    if (i == 0)
    {
        return "0";
    }

    while (i)
    {
        int dig = i % 10;
        char c = dig + '0';
        result += c;
        i /= 10;
    }

    if (i < 0)
    {
        result += '-';
    }

    std::reverse(result.begin(), result.end());

    return result;
}

// time complexity: O(2*N)
// space complexity: O(1)
std::string IntToString_EPI(int x)
{
    bool is_negative = false;
    if (x < 0) {
        is_negative = true;
    }

    std::string s;
    do {
        s += '0' + abs(x % 10);
        x /= 10;
    } while (x);

    s += is_negative ? "-" : "";
    return { std::rbegin(s), std::rend(s) };
}

std::string IntToString(int x)
{
    return IntToString_EPI(x);
}

// time complexity: O(n(1 + logb2 b1)): n multiply-and-adds to get from x from s; logb2 x multiply and adds to get the result
// space complexity: O(1)
std::string ConvertBase_PW(const std::string& num_as_string, int b1, int b2)
{
    // convert to base-10
    int base10 = 0;

    auto char_to_int = [](char c) {
        return isdigit(c) ? c - '0' : c - 55;
    };

    auto int_to_char = [](int i) {
        return i < 10 ? i + '0': i + 55;
    };

    int start_offset = num_as_string[0] == '-' ? 1 : 0;
    for (int i = num_as_string.size() - 1; i >= start_offset; --i)
    {
        int mult = pow(b1, num_as_string.size() - 1 - i);
        int digit = char_to_int(num_as_string[i]);
        base10 += mult * digit;
    }

    std::string result = "";
    while (base10)
    {
        int digit = base10 % b2;
        base10 /= b2;
        char c = int_to_char(digit);
        result += c;
    }

    result += start_offset ? "-" : "";

    std::reverse(result.begin(), result.end());

    return result;
}

std::string ConstructFromBase(int num_as_int, int base) 
{
    return num_as_int == 0 ? ""
                            : ConstructFromBase(num_as_int / base, base) +
                                (char)(num_as_int % base >= 10
                                    ? 'A' + num_as_int % base - 10
                                    : '0' + num_as_int % base);
}

// time complexity: O(n(1 + logb2 b1))
// space complexity: O(1)
std::string ConvertBase_EPI(const std::string& num_as_string, int b1, int b2)
{
    bool is_negative = num_as_string.front() == '-';
    int num_as_int = 
        std::accumulate(std::begin(num_as_string) + is_negative, std::end(num_as_string), 0, 
            [b1](int x, char c) {
                return x * b1 + (isdigit(c) ? c - '0' : c - 'A' + 10);
            });

    return (is_negative ? "-" : "") +
        (num_as_int == 0 ? "0" : ConstructFromBase(num_as_int, b2));
}

std::string ConvertBase(const std::string& num_as_string, int b1, int b2)
{
    return ConvertBase_EPI(num_as_string, b1, b2);
}

// time complexity: O(N)
// space complexity: O(1)
int SSDecodeColID_PW(const std::string& col)
{
    int colVal = 0;
    int fact = 1;
    for (int i = col.size() - 1; i >= 0; i--)
    {
        int val = col[i] - 'A' + 1;
        colVal += val * fact;
        fact *= 26;
    }

    return colVal;
}

// space complexity: O(1)
// time complexity: O(N)
int SSDecodeColID_EPI(const std::string& col)
{
    return std::accumulate(std::begin(col), std::end(col), 0, [](int result, char c) {
        return result * 26 + c - 'A' + 1;
    });
}

int SSDecodeColID(const std::string& col)
{
    return SSDecodeColID_EPI(col);
}

int SSDecodeColIDBase0(const std::string& col)
{
    int idx = 0;
    return std::accumulate(std::begin(col), std::end(col), 0, [&](int result, char c) {
        return result + ((col.size() - 1 - idx++) * 26) * (c - 'A' + 1);
    });
}