#include "Strings.hpp"

#include <unordered_map>
#include <numeric>
#include <unordered_set>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <stack>
#include <set>
#include <map>
#include <locale>

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

// space complexity: O(1)
// time complexity: O(s log s + t log t)
bool isAnagram_PW(std::string s, std::string t)
{
    std::sort(s.begin(), s.end());
    std::sort(t.begin(), t.end());
    return s == t;
}

// time complexity: O(s + t)
// space complexity: O(s)
bool isAnagram_PW2(std::string s, std::string t)
{
    std::unordered_map<char, int> counts;
    for (int i = 0; i < s.size(); ++i)
    {
        if (counts.find(s[i]) == counts.end())
        {
            counts[s[i]] = 1;
        }
        else
        {
            counts[s[i]]++;
        }
    }

    for (int i = 0; i < t.size(); ++i)
    {
        if (counts.find(t[i]) == counts.end())
        {
            return false;
        }
        else
        {
            counts[t[i]]--;
            if (counts[t[i]] == 0)
            {
                counts.erase(t[i]);
            }
        }
    }

    if (counts.size() != 0)
    {
        return false;
    }

    return true;
}

// time complexity: O(s + t)
// space complexity: O(1)
bool isAnagram_PW3(std::string s, std::string t)
{
    char alph[26] = {0};
    
    for (auto c: s)
    {
        alph[c - 'a']++;
    }
    for (auto c: t)
    {
        alph[c - 'a']--;
    }
    for (auto d: alph)
    {
        if (d != 0) return false;
    }
    return true;
}

bool isAnagram(std::string s, std::string t)
{
    return isAnagram_PW3(s, t);
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

// space complexity: O(N)
// time complexity: O(N)
int ReplaceAndRemove_BF(int size, char s[])
{
    char t[size * 2];
    int counter = 0;
    for (int i = 0; i < size; ++i)
    {
        if (s[i] == 'a')
        {
            t[counter++] = 'd';
            t[counter++] = 'd';
        }
        else if (s[i] == 'b')
        {
            continue;
        }
        else
        {
            t[counter++] = s[i];
        }
    }

    for (int i = 0; i < counter; ++i)
    {
        s[i] = t[i];
    }

    return counter;
}

// space complexity: O(1)
// time complexity: O(2*N + N^2)
int ReplaceAndRemove_PW(int size, char s[])
{
    int a_count = 0;
    int b_count = 0;
    int non_b_count = 0;

    // count a's and b's
    for (int i = 0; i < size; i++)
    {
        if (s[i] == 'a') a_count++;
        if (s[i] == 'b') b_count++;
    }

    non_b_count = size - b_count;

    // remove b's
    int counter1 = 0, counter2 = 0;
    while (counter1 < size)
    {
        if (s[counter1] == 'b')
        {
            // do nothing
        }
        else
        {
            s[counter2++] = s[counter1];
        }

        counter1++;
    }

    // double d's
    counter1 = 0;
    int used_a_count = 0;
    while (counter1 < (non_b_count + a_count))
    {
        if (s[counter1] == 'a')
        {
            s[counter1++] = 'd';
            counter2 = counter1;
            char prev = 'd';
            used_a_count++;
            while (counter2 < (non_b_count + used_a_count))
            {
                char cur = s[counter2];
                s[counter2] = prev;
                prev = cur;
                counter2++;
            }
        }

        counter1++;
    }

    return non_b_count + a_count;
}

// space complexity: O(1)
// time complexity: O(N)
int ReplaceAndRemove_PWLinear(int size, char s[])
{
    // remove b's, get new size
    int counter1 = 0, counter2 = 0, a_count = 0;
    while (counter1 < size)
    {
        if (s[counter1] == 'b')
        {
            // do nothing
        }
        else
        {
            if (s[counter1] == 'a') a_count++;
            s[counter2++] = s[counter1];
        }

        counter1++;
    }

    int new_size = counter2 + a_count;
    
    // double d's
    counter1 = counter2 - 1;
    counter2 = new_size - 1;
    while (counter2 >= 0)
    {
        if (s[counter1] == 'a')
        {
            s[counter2--] = 'd';
            s[counter2--] = 'd';
            counter1--;
        }
        else
        {
            s[counter2--] = s[counter1--];
        }
    }

    return new_size;
}

// space complexity: O(1)
// time complexity: O(N)
int ReplaceAndRemove_EPI(int size, char s[])
{
    // Forward iteration: remove 'b's and count the number of 'a's
    int write_idx = 0, a_count = 0;
    for (int i = 0; i < size; ++i)
    {
        if (s[i] != 'b')
        {
            s[write_idx++] = s[i];
        }
        if (s[i] == 'a')
            ++a_count;
    }
    
    // Backward iteration: replace 'a's with 'dd's starting frm the end.
    int cur_idx = write_idx - 1;
    write_idx = write_idx + a_count - 1;
    const int final_size = write_idx + 1;
    while (cur_idx >= 0)
    {
        if (s[cur_idx] == 'a')
        {
            s[write_idx--] = 'd';
            s[write_idx--] = 'd';
        }
        else
        {
            s[write_idx--] = s[cur_idx];
        }
        --cur_idx;
    }
    return final_size;
}

int ReplaceAndRemove(int size, char s[])
{
    return ReplaceAndRemove_EPI(size, s);
}

bool IsPalindrome_BF(const std::string& s)
{
    std::string transformed;
    std::copy_if(s.begin(), s.end(), std::back_inserter(transformed), [](char c) {
        return isalpha(c);
    });
    
    std::string lower;
    std::transform(transformed.begin(), transformed.end(), std::back_inserter(lower), [](char c) {
        return std::tolower(c);
    });

    std::swap(lower, transformed);
    std::cout << transformed << std::endl;

    for (int i = 0; i < transformed.size(); ++i)
    {
        if (transformed[i] != transformed[transformed.size() - 1 - i])
        {
            return false;
        }
    }

    return true;
}

// space complexity: O(1)
// time complexity: O(n)
bool IsPalindrome_Linear(const std::string s)
{
    int i = 0;
    int j = s.size() - 1;
    while (i < j)
    {
        if (!std::isalpha(s[i]))
        {
            i++;
        }
        else if (!std::isalpha(s[j]))
        {
            j--;
        }
        else if (std::tolower(s[i]) != std::tolower(s[j]))
        {
            return false;
        }
        else
        {
            i++;
            j--;
        }
    }

    return true;
}

// space complexity: O(1)
// time complexity: O(n)
bool IsPalindrome_EPI(const std::string s)
{
    // i moves forward, and j moves backward.
    int i = 0;
    int j = size(s) - 1;
    while (i < j)
    {
        // i and j both skip non-alphanumeric characters
        while (!isalnum(s[i]) && i < j)
        {
            ++i;
        }
        while (!isalnum(s[j]) && i < j)
        {
            --j;
        }
        if (tolower(s[i++]) != tolower(s[j--]))
        {
            return false;
        }
    }

    return true;
}

bool IsPalindrome(const std::string& s)
{
    return IsPalindrome_EPI(s);
}

// space complexity: O(1)
// time complexity: O(N)
void ReverseWords_PW(std::string * s)
{
    std::string& str = *s;

    // reverse characters in string to get correct ordering of strings
    int i = 0, j = str.size() - 1;
    while (i < j)
    {
        std::swap(str[i++], str[j--]);
    }

    // reverse characters in each word
    i = 0, j = 0;
    while (j < str.size())
    {
        while (str[j] == ' ' && j < str.size()) j++;

        if (j >= str.size()) break;

        i = j;
        while (str[j] != ' ' && j < str.size()) j++;

        int counter = j;
        j--;

        while (i < j) std::swap(str[i++], str[j--]);
        j = counter;
    }
}

// space complexity: O(1)
// time complexity: O(N)
void ReverseWords_EPI(std::string * s)
{
    // First, reverse the whole string
    std::reverse(std::begin(*s), std::end(*s));

    size_t start = 0, finish;
    while ((finish = s->find(" ", start)) != std::string::npos)
    {
        // Reverses each word in the string
        std::reverse(std::begin(*s) + start, std::begin(*s) + finish);
        start = finish + 1;
    }

    // // Reverses the last word
    std::reverse(std::begin(*s) + start, std::end(*s));
}


void ReverseWords(std::string * s)
{
    return ReverseWords_EPI(s);
}

std::string ReverseWordsLC(std::string s)
{
    std::string str = s;

    // reverse characters in string to get correct ordering of strings

    int i = 0, j = str.size() - 1;
    int spacesRight = 0;
    while (j > i)
    {
        if (str[j--] == ' ')
        {
            spacesRight++;
        }
        else 
        {
            break;
        }
    }
    j = str.size() - 1 - spacesRight;
    int spacesLeft = 0;
    while (i < j)
    {
        if (str[i++] == ' ')
        {
            spacesLeft++;
        }
        else 
        {
            break;
        }
    }

    i = 0, j = str.size() - 1 - spacesRight;
    while (i < j)
    {
        std::swap(str[i++], str[j--]);
    }

    // reverse characters in each word
    i = 0, j = 0;
    while (j < (str.size() - spacesRight))
    {
        while (str[j] == ' ' && (j < (str.size() - spacesRight))) j++;

        if (j >= str.size()) break;

        i = j;
        while (str[j] != ' ' && (j < (str.size() - spacesRight))) j++;

        int counter = j;
        j--;
        
        while (i < j) std::swap(str[i++], str[j--]);
        j = counter;
    }

    return str.substr(0, str.size() - (spacesRight + spacesLeft));
}

int GetNextInSeq(int n)
{
    int curNum = n % 10;
    int prevNum = curNum;
    int curCount = 1;
    n /= 10;
    int mult = 1;
    int num = 0;
    while (true)
    {
        if (!n) break;

        // std::cout << "CurNum: " << curNum << std::endl;
        // std::cout << "Prev num: " << prevNum << std::endl;
        // std::cout << "n: " << n << std::endl;
        // std::cout << "Cur count: " << curCount << std::endl;
        // std::cout << "Num: " << num << std::endl;

        prevNum = curNum;
        curNum = n % 10;
        n /= 10;
        if (curNum == prevNum)
        {
            curCount++;
        }
        else 
        {
            num += prevNum * mult;
            mult *= 10;
            num += curCount * mult;
            mult *= 10;
            curCount = 1;
        }
    }

                num += curNum * mult;
                mult *= 10;
                num += curCount * mult;
                curCount = 1;
    
    return num;
}

// O(2^N * N + N), number of digits is at most 2 times number of digits (last N for string conversion)
// time complexity: O(N^2), could be reduced by caching
// space complexity: O(1)
std::string LookAndSay_PW(int n)
{
    if (n == 1) return std::to_string(n);

    int seed = 1;
    for (int i = 1; i < n; ++i)
    {
        seed = GetNextInSeq(seed);
    }

    return std::to_string(seed);
}

std::string NextNumber(const std::string& s)
{
    std::string result;
    for (int i = 0; i < std::size(s); ++i)
    {
        int count = 1;
        while (i + 1 < std::size(s) && s[i] == s[i + 1])
        {
            ++i, ++count;
        }
        result += std::to_string(count) + s[i];
    }
    return result;
}

// each successive number can have at most twice as many digits as the previous number
// this happens when all digits are different
// maximum length number has length of no more than 2^N
// O(N*2^N)
std::string LookAndSay_EPI(int n)
{
    std::string s = "1";
    for (int i = 1; i < n; ++i) {
        s = NextNumber(s);
    }
    return s;
}

std::string LookAndSay(int n)
{
    return LookAndSay_EPI(n);
}

// space complexity: O(1)
// time complexity: O(N)
int RomanToInteger_PW(const std::string& s)
{
    int sum = 0;
    char prev = ' ';
    for (int i = 0; i < s.size(); ++i)
    {
        switch (s[i])
        {
            case 'I':
                sum += 1;
                break;
            case 'V':
                sum += 5;
                if (prev == 'I') sum--;
                break;
            case 'X':
                sum += 10;
                if (prev == 'I') sum -= 2;
                else if (prev == 'V') sum -= 10;
                break;
            case 'L':
                sum += 50;
                if (prev == 'I') sum -= 2;
                else if (prev == 'V') sum -= 10;
                else if (prev == 'X') sum -= 20;
                break;
            case 'C':
                sum += 100;
                if (prev == 'I') sum -= 2;
                else if (prev == 'V') sum -= 10;
                else if (prev == 'X') sum -= 20;
                else if (prev == 'L') sum -= 100;
                break;
            case 'D':
                sum += 500;
                if (prev == 'I') sum -= 2;
                else if (prev == 'V') sum -= 10;
                else if (prev == 'X') sum -= 20;
                else if (prev == 'L') sum -= 100;
                else if (prev == 'C') sum -= 200;
                break;
            case 'M':
                sum += 1000;
                if (prev == 'I') sum -= 2;
                else if (prev == 'V') sum -= 10;
                else if (prev == 'X') sum -= 20;
                else if (prev == 'L') sum -= 100;
                else if (prev == 'C') sum -= 200;
                else if (prev == 'D') sum -= 1000;
                break;
        }

        prev = s[i];
    }

    return sum;
}

// space complexity: O(1)
// time complexity: O(N)
int RomanToInteger_EPI(const std::string& s)
{
    std::unordered_map<char, int> T = {{'I', 1}, { 'V', 5}, {'X', 10}, {'L', 50},
                                       {'C', 100}, {'D', 500}, {'M', 1000}};

    int sum = T[s.back()];
    for (int i = s.length() - 2; i >= 0; --i)
    {
        if (T[s[i]] < T[s[i + 1]])
        {
            sum -= T[s[i]];
        }
        else
        {
            sum += T[s[i]];
        }
    }

    return sum;
}

int RomanToInteger(const std::string& s)
{
    return RomanToInteger_EPI(s);
}

bool isValidSegment(const std::string& s)
{
    if (!(s.size() <= 3 && s.size() >= 1))
    {
        return false;
    }
    else if (s.size() > 1 && s[0] == '0')
    {
        return false;
    }
    else if (std::stoi(s) > 255)
    {
        return false;
    }

    return true;
}

// O(1) time complexity since total number of IP addresses is constant (2^32)
std::vector<std::string> GetValidIpAddress_PW(const std::string& s)
{
    std::vector<std::string> addresses;

    for (int i = 0; i < 3 && i < s.size(); i++)
    {
        if (!isValidSegment(s.substr(0, i + 1))) continue;
        for (int j = i + 1; j < i + 4 && j < s.size(); j++)
        {
            if (!isValidSegment(s.substr(i + 1, j - i))) continue;
            for (int k = j + 1; k < j + 4 && k < s.size(); k++)
            {
                if (!isValidSegment(s.substr(j + 1, k - j))) continue;
                for (int l = k + 1; l < k + 4 && l < s.size(); l++)
                {
                    if (!isValidSegment(s.substr(k + 1, l - k)) || l < s.size() - 1)
                    {
                        continue;
                    }

                    addresses.push_back(
                        s.substr(0, i + 1) + "." + 
                        s.substr(i + 1, j - i) + "." + 
                        s.substr(j + 1, k - j) + "." + 
                        s.substr(k + 1, l - k));
                }
            }
        }
    }

    return addresses;
}

bool IsValidPart(const std::string& s)
{
    if (std::size(s) > 3) {
        return false;
    }
    // "00", "000", "01", etc. are not valid, but "0" is valid.
    if (s.front() == '0' && std::size(s) > 1) {
        return false;
    }
    int val = std::stoi(s);
    return val <= 255 && val >= 0;
}

// O(1) time complexity since total number of IP addresses is constant (2^32)
std::vector<std::string> GetValidIpAddress_EPI(const std::string& s)
{
    std::vector<std::string> result;
    for (int i = 1; i < 4 && i < std::size(s); ++i) {
        if (const std::string first = s.substr(0, i); IsValidPart(first)) {
            for (size_t j = 1; i + j < std::size(s) && j < 4; ++j) {
                const std::string second = s.substr(i, j);
                if (IsValidPart(second)) {
                    for (size_t k = 1; i + j + k < std::size(s) && k < 4; ++k) {
                        const std::string third = s.substr(i + j, k),
                                     fourth = s.substr(i + j + k);
                        if (IsValidPart(third) && IsValidPart(fourth)) {
                            result.emplace_back(first + "." + second + "." + third + "." + 
                                fourth);
                        }
                    }
                }
            }
        }
    }

    return result;
}

std::vector<std::string> GetValidIpAddress(const std::string& s)
{
    return GetValidIpAddress_EPI(s);
}

// time complexity: O(n), each of three iterations takes O(n) time
std::string SnakeString_PW(const std::string& s)
{
    std::string snake = "";

    // row 0
    // std::cout << std::string(1, ' ');
    for (int i = 1; i < s.size(); i += 4)
    {
        // std::cout << s[i] << std::string(3, ' ');
        snake += s[i];
    }

    // std::cout << std::endl;

    // row 1
    for (int i = 0; i < s.size(); i += 2)
    {
        // std::cout << s[i] << std::string(1, ' ');
        snake += s[i];
    }

    // std::cout << std::endl;

    // row 2
    // std::cout << std::string(3, ' ');
    for (int i = 3; i < s.size(); i += 4)
    {
        // std::cout << s[i] << std::string(3, ' ');
        snake += s[i];
    }

    // std::cout << std::endl;

    return snake;
}

// time complexity: O(n), each of three iterations takes O(n) time
std::string SnakeString_EPI(const std::string& s)
{
    std::string result = "";

    // Outputs the first row, i.e., s[1], s[5], s[9], ...
    for (int i = 1; i < std::size(s); i += 4) {
        result += s[i];
    }

    // Outputs the second row, i.e., s[0], s[2], s[4], ...
    for (int i = 0; i < std::size(s); i += 2) {
        result += s[i];
    }

    // Outputs the third row, i.e., s[3], s[7], s[11], ...
    for (int i = 3; i < std::size(s); i += 4) {
        result += s[i];
    }
    return result;
}

std::string SnakeString(const std::string& s)
{
    return SnakeString_EPI(s);
}

std::string ZigZagString(const std::string& s)
{
    return "";
}

// time complexity: O(N)
// space complexity: O(1)
std::string Encode_PW(const std::string& s)
{
    if (s.empty()) return s;

    std::string result = "";
    char c = s[0];
    size_t len = 1;

    for (size_t i = 1; i < s.size(); ++i)
    {
        if (s[i] == c)
        {
            ++len;
        }
        else
        {
            result += std::to_string(len) + c;
            c = s[i];
            len = 1;
        }
    }

    result += std::to_string(len) + c;
    return result;
}

// time complexity: O(N)
// space complexity: O(1)
std::string Decode_PW(const std::string& s)
{
    std::string result = "";
    std::string lenStr = "";
    for (int i = 0; i < s.size(); ++i)
    {
        if (isdigit(s[i]))
        {
            lenStr += s[i];
        }
        else
        {
            size_t len = std::stoi(lenStr);
            for (int j = 0; j < len; ++j)
            {
                result += s[i];
            }
            lenStr = "";
        }
    }
    return result;
}

// time complexity: O(N)
// space complexity: O(1)
std::string Encode_EPI(const std::string& s)
{
    std::string result = "";
    for (int i = 1, count = 1; i <= std::size(s); ++i) {
        if (i == std::size(s) || s[i] != s[i - 1]) {
            // Found new character so write the count of the previous character
            result += std::to_string(count) + s[i - 1];
            count = 1;
        } else {    // s[i] == s[i - 1].
            ++count;
        }
    }
    return result;
}

// time complexity: O(N)
// space complexity: O(1)
std::string Decode_EPI(const std::string& s)
{
    int count = 0;
    std::string result = "";
    for (const char& c: s) {
        if (isdigit(c)) {
            count = count * 10 + c - '0';
        } else {
            result.append(count, c);
            count = 0;
        }
    }
    return result;
}

std::string Encode(const std::string& s)
{
    return Encode_EPI(s);
}

std::string Decode(const std::string& s)
{
    return Decode_EPI(s);
}

// space complexity: O(1)
// time complexity: O(N^2)
int findStr_PW(const std::string& s, const std::string& t)
{
    bool foundStr = false;
    int foundIdx = -1;

    if (t.empty()) { return 0; }

    for (size_t i = 0; i < t.size(); ++i)
    {
        if (t[i] == s[0])
        {
            if (i + s.size() > t.size())
            {
                foundStr = false;
                break;
            }

            foundStr = true;
            int j = 1;
            for (; j < s.size() && (j + i) < t.size(); ++j)
            {
                if (t[i + j] == s[j])
                {
                    continue;
                }
                else
                {
                    foundStr = false;
                    break;
                }
            }

            if (foundStr)
            {
                foundIdx = i;
                return foundIdx;
            }
        }
    }

    return foundIdx;
}

// time complexity: O(M + N) with good hashing algorithm
// space compexity: O(1)
// Returns the index of the first character of the substring if found, -1 otherwise.
int findStr_RobinKarp(const std::string& s, const std::string& t)
{
    if (std::size(s) > std::size(t)) {
        return -1; // s is not a substring of t
    }

    if (s.empty()) {
        return 0;
    }

    const int kBase = 26;
    int t_hash = 0, s_hash = 0;  // Hash codes for the substring of t and s.
    int power_s = 1;             // KBase^|s-1|.
    for (int i = 0; i < std::size(s); ++i) {
        power_s = i ? power_s * kBase : 1;
        t_hash = t_hash * kBase + t[i];
        s_hash = s_hash * kBase + s[i];
    }

    for (int i = std::size(s); i < std::size(t); ++i) {
        // Checks the two substrings are actually equal or not, to protect against
        // hash collision.
        if (t_hash == s_hash && !t.compare(i - std::size(s), std::size(s), s)) {
            return i - size(s);
        }

        // Uses rolling hash to compute the new hash code
        t_hash -= t[i - std::size(s)] * power_s;
        t_hash = t_hash * kBase + t[i];
    }

    // Tries to match s and t[size(t) - size(s), size(t) - 1]
    if (t_hash == s_hash && t.compare(std::size(t) - std::size(s), std::size(s), s) == 0) {
        return std::size(t) - std::size(s);
    }

    return -1; // s is not a substring of t;
}

int findStr(const std::string& s, const std::string& t)
{
    return findStr_RobinKarp(s, t);
}

std::vector<std::string> permRest(std::string rest)
{
    if (rest.size() == 0)
    {
        return {""};
    }
    else {
        std::vector<std::string> new_result;
        auto result = permRest(rest.substr(1));
        if (isalpha(rest[0]))
        {
            for (auto combo: result)
            {
                new_result.push_back(std::tolower(rest[0], std::locale()) + combo);
                new_result.push_back(std::toupper(rest[0], std::locale()) + combo);
            }
            // std::copy(new_rest.begin(), new_rest.end(), rest.begin() + 1);
            // auto result = std
        }
        else
        {
            for (auto combo: result)
            {
                new_result.push_back(rest[0] + combo);
            }
        }

        return new_result;
    }
}

std::vector<std::string> letterCasePermutation(std::string S)
{
    return permRest(S);
}

std::string addStrings(std::string num1, std::string num2)
{
    std::string larger = num1.size() >= num2.size() ? num1 : num2;
    std::string smaller = num1.size() < num2.size() ? num1 : num2;
    int carry = 0;
    std::string sumStr = "";
    for (int i = 0; i < smaller.size(); ++i)
    {
        int op1 =  num1[num1.size() - i - 1] - '0';
        int op2 =  num2[num2.size() - i - 1] - '0';
        int sum = (op1 + op2 + carry) % 10;
        char sumCh = sum + '0';
        sumStr = sumCh + sumStr;
        carry = (op1 + op2 + carry) / 10;
    }
    
    for (int i = smaller.size(); i < larger.size(); ++i)
    {
        int op1 = larger[larger.size() - i - 1] - '0';
        int op2 = 0;
        int sum = (op1 + op2 + carry) % 10;
        char sumCh = sum + '0';
        sumStr = sumCh + sumStr;
        carry = (op1 + op2 + carry) / 10;
    }

    if (carry)
    {
        char sumCh = carry + '0';
        sumStr = sumCh + sumStr;
    }

    return sumStr;
}

// time complexity: O(n)
// space complexity: O(n)
bool buddyStrings(std::string A, std::string B)
{
    if (A.size() != B.size() || A.empty())
    {
        return false;
    }

    int first = -1;
    int second = -1;
    std::unordered_map<char, int> counts;
    for (int i = 0; i < A.size(); ++i)
    {
        counts[A[i]]++;
        if (A[i] != B[i])
        {
            if (first > 0 && second > 0)
            {
                // more than 1 swap (possibly) required
                return false;
            }
            else if (first == -1)
            {
                first = i;
            }
            else 
            {
                second = i;
                std::swap(A[first], A[second]);

                if (A[first] != B[first] || A[second] != B[second])
                {
                    return false;
                }
            }
        }
    }

    if (first != -1 && second == -1)
    {
        return false;
    }

    if (first == -1 || second == -1)
    {

        for (auto pair: counts)
        {
            if (pair.second > 1)
            {
                return true;
            }
        }
        return false;
    }

    return true;
}

// time complexity: O(log n)
// space complexity: O(log n)
std::string convertToTitle(int n)
{
    std::string title = "";

    while (n)
    {   
        char c = (char)(((n - 1) % 26) + 65);
        title = c + title;
        n = (n - 1) / 26;
    }

    return title;
}

// time complexity: O(1)
// space complexity: O(n)
std::string defangIPaddr_PW1(std::string address)
{
    std::string defanged;
    for (int i = 0; i < address.size(); ++i)
    {
        if (address[i] == '.')
        {
            defanged += "[.]";
        }
        else
        {
            defanged += address[i];
        }
    }

    return defanged;
}

// time complexity: O(n)
// space complexity: O(n)
std::string defangIPaddr_PW2(std::string address)
{
    size_t pos = address.find(".");
    while(pos != std::string::npos) 
    {
        address.replace(pos, 1, "[.]");
        pos = address.find(".", pos + 3);
    }

    return address;
}

std::string defangIPaddr(std::string address)
{
    return defangIPaddr_PW2(address);
}

// time complexity: O(3*(len(s) + len(T))), traverse once each to append to stack, traverse once to append to string, traverse once to compare
// space complexity: O(3 * n), stack must match size of longest string, also size of actual strings
bool backspaceCompare(std::string S, std::string T)
{
    std::stack<char> a;
    std::string sResult, tResult;
    for (auto c: S)
    {
        if (c == '#' && !a.empty())
        {
            a.pop();
        }
        else if (c == '#')
        {
            continue;
        }
        else
        {
            a.push(c);
        }
    }

    while (!a.empty())
    {
        sResult += a.top();
        a.pop();
    }

    for (auto c: T)
    {
        if (c == '#' && !a.empty())
        {
            a.pop();
        }
        else if (c == '#')
        {
            continue;
        }
        else
        {
            a.push(c);
        }
    }

    while (!a.empty())
    {
        tResult += a.top();
        a.pop();
    }

    return sResult == tResult;
}

// time complexity: O(log n)
// space complexity: O(n)
std::string convertToBase7(int num)
{
    std::string s = "";
    std::string sign = num < 0 ? "-" : "";
    num = std::abs(num);

    if (!num)
    {
        return "0";
    }

    while (num)
    {
        std::string c = std::to_string(num % 7);
        s = c + s;
        num /= 7;
    }

    s = sign + s;

    return s;
}

// time complexity: O(m + n)
// space complexity: O(1)
bool arrayStringsAreEqual(std::vector<std::string>& word1, std::vector<std::string>& word2)
{
    int i1 = 0, j1 = 0;
    int i2 = 0, j2 = 0;
    while (i1 < word1.size() && i2 < word2.size())
    {
        if (j1 >= word1[i1].size())
        {
            i1++;
            j1 = 0;
        }
        if (j2 >= word2[i2].size())
        {
            i2++;
            j2 = 0;
        }

        if (i1 >= word1.size() && i2 >= word2.size())
        {
            break;
        }
        else if (i1 >= word1.size())
        {
            return false;
        }
        else if (i2 >= word2.size())
        {
            return false;
        }

        if (word1[i1][j1] != word2[i2][j2])
        {
            return false;
        }

        j1++;
        j2++;
    }

    return true;
}

// time complexity: O(n)
// space complexity: O(1)
int isPrefixOfWord(std::string sentence, std::string searchWord)
{
    bool inWord = false;
    bool matchingPrefix = true;
    int wordIndex = 1;
    int charIndex = 0;
    for (int i = 0; i < sentence.size(); ++i)
    {
        if (sentence[i] == ' ' && inWord)
        {
            inWord = !inWord;
            wordIndex++;
            charIndex = 0;
        }   
        else if (isalpha(sentence[i]) && !inWord)
        {
            inWord = true;
            if (sentence[i] == searchWord[charIndex])
            {
                matchingPrefix = true;
                charIndex++;
                
                if (charIndex == searchWord.size())
                {
                    return wordIndex;
                }
            }
            else
            {
                matchingPrefix = false;
            }
        }
        else if (isalpha(sentence[i]) && inWord && matchingPrefix)
        {
            if (sentence[i] == searchWord[charIndex])
            {
                matchingPrefix = true;
                charIndex++;
            }
            else
            {
                matchingPrefix = false;
                charIndex = 0;
            }

            if (charIndex == searchWord.size())
            {
                return wordIndex;
            }
        }
    }

    return -1;
}

// time complexity: O(n)
// space complexity: O(1)
int maxPower(std::string s)
{
    if (s.empty())
    {
        return 0;
    }

    int curCount = 1;
    int maxCount = curCount;
    for (int i = 1; i < s.size(); ++i)
    {
        if (s[i] == s[i - 1])
        {
            curCount++;
            maxCount = std::max(maxCount, curCount);
        }
        else
        {
            curCount = 1;
        }
    }

    return maxCount;
}

// time complexity: O(n)
// space complexity: O(1)
bool checkOnesSegment(std::string s)
{
    bool inLeadingOnes = true;
    for (int i = 0; i < s.size(); ++i)
    {
        if (s[i] == '0' && inLeadingOnes)
        {
            inLeadingOnes = false;
        }
        else if (s[i] == '1' && !inLeadingOnes)
        {
            return false;
        }
    }

    return true;
}

// time complexity: O(1), dependent on number of bits (32 bits / 16 nibbles)
// space complexity: O(1), at max 8 bytes to represent
std::string toHex(int num)
{
    std::string result = "";

    auto getChar = [](int n) {
        if (n < 10) {
            return (char)(n + '0');
        } else {
            switch (n) {
                case 10:
                    return 'a';
                case 11:
                    return 'b';
                case 12:
                    return 'c';
                case 13:
                    return 'd';
                case 14:
                    return 'e';
                case 15:
                    return 'f';
            }
        }

        return ' ';
    };

    for (int i = 0; i < sizeof(num) * 2; ++i)
    {
        auto c = getChar(num & 0xf);
        result = c + result;
        num >>= 4;

        if (!num) break;
    }

    return result;
}

bool isLongPressedName(std::string name, std::string typed)
{
    if (typed.size() < name.size())
    {
        return false;
    }

    int counter1 = 0, counter2 = 0;
    while (counter1 < name.size() && counter2 < typed.size())
    {
        if (name[counter1] == typed[counter2])
        {
            counter1++;
            counter2++;
        }
        else if (name[counter1] != typed[counter2] && (counter1 > 0 && name[counter1 - 1] == typed[counter2]))
        {
            counter2++;
        }
        else if (name[counter1] != typed[counter2])
        {
            return false;
        }
    }

    while (counter2 < typed.size())
    {
        if (typed[counter2] != name[name.size() - 1])
        {
            return false;
        }
        counter2++;
    }

    if (counter1 < name.size())
    {
        return false;
    }

    return true;
}

// time complexity: O(l + c), where l is length of allowed and c is number of characters across all words
// space complexity: O(l) (unordered set creation)
int countConsistentStrings(std::string allowed, std::vector<std::string>& words)
{
    int count = 0;
    std::unordered_set<char> allowed_set;
    for (auto c: allowed)
    {
        allowed_set.insert(c);
    }

    for (auto word: words)
    {
        bool goodWord = true;
        for (auto c: word)
        {
            if (allowed_set.find(c) == allowed_set.end())
            {
                goodWord = false;
                break;
            }
        }

        if (goodWord)
        {
            count++;
        }
    }

    return count;
}

// time complexity: O(n)
// space complexity: O(n^2)
std::string freqAlphabets(std::string s)
{
    std::string result = "";
    int multiDigitCounter = 0;
    std::string num = "";
    for (int i = s.size() - 1; i >= 0; --i)
    {
        if (s[i] == '#')
        {
            multiDigitCounter = 2;
        }
        else if (multiDigitCounter)
        {
            num = s[i] + num;
            multiDigitCounter--;
        }

        if (!num.empty() && !multiDigitCounter)
        {
            int numInt = std::stoi(num);
            result = (char)(numInt - 1 + 'a') + result;
            num = "";
        }
        else if (num.empty() && !multiDigitCounter)
        {
            int num = s[i] - 49;
            result = (char)(num + 'a') + result;
        }
    }

    return result;
}

// time complexity: O(n)
// space complexity: O(1)
bool halvesAreAlike(std::string s)
{
    int vowelCount1 = std::count_if(s.begin(), s.begin() + s.size() / 2, [](char c) {
        return std::tolower(c) == 'a' || std::tolower(c) == 'i' || std::tolower(c) == 'e' || std::tolower(c) == 'o' || std::tolower(c) == 'u';
    });
    int vowelCount2 = std::count_if(s.begin() + s.size() / 2, s.end(), [](char c) {
        return std::tolower(c) == 'a' || std::tolower(c) == 'i' || std::tolower(c) == 'e' || std::tolower(c) == 'o' || std::tolower(c) == 'u';
    });
    return vowelCount1 == vowelCount2;
}

// time complexity: O(n)
// space complexity: O(1)
int titleToNumber(std::string columnTitle)
{
    int column = 0;
    long long factor = 1;
    for (int i = columnTitle.size() - 1; i >= 0; --i)
    {
        column += (columnTitle[i] - 64) * factor;
        factor *= 26;
    }
    return column;
}

// time complexity: O(m * n), need to traverse each character to count and identify min count
// space complexity: O(m * n) for map which contains each character and count for each word
std::vector<std::string> commonChars_PW1(std::vector<std::string>& A)
{
    std::map<char, std::vector<int>> charCounts;
    for (size_t i = 0; i < A.size(); ++i)
    {
        for (size_t j = 0; j < A[i].size(); ++j)
        {
            if (charCounts.find(A[i][j]) == charCounts.end())
            {
                std::vector<int> counts(A.size());
                charCounts[A[i][j]] = counts;
                charCounts[A[i][j]][i]++;
            }
            else
            {
                charCounts[A[i][j]][i]++;
            }
        }
    }

    std::vector<std::string> result;
    for (auto pair: charCounts)
    {
        int min = std::numeric_limits<int>::max();
        for (auto val: pair.second)
        {
            min = std::min(val, min);
        }
        
        if (min > 0)
        {
            for (size_t i = 0; i < min; ++i)
            {
                std::string str = std::string(1, pair.first);
                result.push_back(str);
            }
        }
    }

    return result;
}

// time complexity: O(m * n), where m is number of strings and n is length of each string
// space complexity: O(1) just need two vectors of size 26 characters
std::vector<std::string> commonChars_PW2(std::vector<std::string>& A)
{
    std::vector<int> count(26, std::numeric_limits<int>::max());
    for (size_t i = 0; i < A.size(); ++i)
    {
        std::vector<int> count1(26, 0);
        for (size_t j = 0; j < A[i].size(); ++j)
        {
            int k = (int)A[i][j] - 'a';
            count1[k]++;
        }

        for (size_t j = 0; j < count.size(); ++j)
        {
            count[j] = std::min(count1[j], count[j]);
        }
    }

    std::vector<std::string> result;
    for (size_t i = 0; i < count.size(); ++i)
    {
        if (count[i] > 0)
        {
            for (int j = 0; j < count[i]; ++j)
            {
                std::string str = std::string(1, i + 'a');
                result.push_back(str);
            }
        }
    }

    return result;
}

std::vector<std::string> commonChars(std::vector<std::string>& A)
{
    return commonChars_PW2(A);
}

// space complexity: O(1)
// time complexity: O(n^2)
bool areAlmostEqual_PW1(std::string s1, std::string s2)
{
    if (s1.size() != s2.size()) return false;

    if (s1.empty()) return true;

    for (int i = 0; i < s1.size(); ++i)
    {
        for (int j = i; j < s1.size(); ++j)
        {
            std::string temp = s1;
            std::swap(temp[i], temp[j]);
            if (temp == s2) return true;
        }
    }

    return false;
}

// time complexity: O(n)
// space complexity: O(1)
bool areAlmostEqual_PW2(std::string s1, std::string s2)
{
    if (s1.size() != s2.size()) return false;

    int i1 = -1, i2 = -1, numDiff = 0;
    for (int i = 0; i < s1.size(); ++i)
    {
        if (s1[i] != s2[i])
        {
            numDiff++;
            if (i1 == -1)
            {
                i1 = i;
            }
            else if (i2 == -1)
            {
                i2 = i;
            }
            else
            {
                return false;
            }
        }
    }

    if (numDiff == 1) return false;
    if (numDiff == 0) return true;
    if (numDiff > 2) return false;

    std::swap(s1[i1], s1[i2]);

    return s1 == s2;
}

bool areAlmostEqual(std::string s1, std::string s2)
{
    return areAlmostEqual_PW2(s1, s2);
}

// time complexity: O(n)
// space complexity: O(1)
std::string interpret(std::string command)
{
    char lookahead;
    if (command.size() > 1)
    {
        lookahead = command[1];
    }

    std::string interpreted = "";
    for (int i = 0; i < command.size(); )
    {
        if (command[i] == 'G')
        {
            interpreted += 'G';
            i++;
        }
        else if (command[i] == '(' && lookahead == ')')
        {
            interpreted += 'o';
            i += 2;
        }
        else if (command[i] == '(' && lookahead == 'a')
        {
            interpreted += "al";
            i += 4;
        }

        if (i < command.size() - 1) 
        {
            lookahead = command[i + 1];
        }
    }

    return interpreted;
}

// time complexity: O(n)
// space complexity: O(1)
std::string toGoatLatin(std::string S)
{
    std::string result;
    auto isVowel = [](char c) {
        c = std::tolower(c);
        switch (c)
        {
            case 'a':
            case 'e':
            case 'i':
            case 'o':
            case 'u':
                return true;
        }

        return false;
    };

    bool leadingConsonant = false, inWord = false;
    char leadConsonant = ' ';
    int wordCount = 1;

    for (int i = 0; i < S.size(); ++i)
    {
        if (S[i] == ' ')
        {
            if (leadingConsonant)
            {
                result += leadConsonant; 
            }

            result += "ma";

            for (int i = 0; i < wordCount; ++i)
            {
                result += "a";
            }

            wordCount++;
            result += " ";
            leadingConsonant = inWord = false;
            continue;
        }
        
        if (!inWord)
        {
            inWord = true;
            if (!isVowel(S[i]))
            {
                leadingConsonant = true;
                leadConsonant = S[i];
                continue;
            }
        }

        result += S[i];
    }

    if (leadingConsonant)
    {
        result += leadConsonant; 
    }

    result += "ma";

    for (int i = 0; i < wordCount; ++i)
    {
        result += "a";
    }

    return result;
}

// space complexity: O(1)
// time complexity: O(n)
std::string generateTheString(int n)
{
    if (n % 2 == 0)
    {
        std::string result(n-1, 'x');
        result += "y";
        return result;
    }
    else
    {
        std::string result(n, 'x');
        return result;
    }
}

// time complexity: O(2 * n log n + n)
// space complexity: O(1)
char findTheDifference_PW1(std::string s, std::string t)
{
    std::sort(s.begin(), s.end());
    std::sort(t.begin(), t.end());

    for (int i = 0; i < s.size(); ++i)
    {
        if (s[i] != t[i])
        {
            return t[i];
        }
    }

    return t[t.size() - 1];
}

// time complexity: O(n)
// space complexity: O(1)
char findTheDifference_PW2(std::string s, std::string t)
{
    char r = 0;
    for (char c: s)
    {
        r ^= c;
    }
    for (char c: t) 
    {
        r ^= c;
    }

    return r;
}

char findTheDifference(std::string s, std::string t)
{
    return findTheDifference_PW2(s, t);
}

// time complexity: O(n * k + m), where m is size of char, n is size of words and k is size of average word
// space complexity: O(m * n), where m is size of char, n is number of words
int countCharacters_PW1(std::vector<std::string>& words, std::string chars)
{
    std::unordered_map<char, int> counts;
    for (auto c: chars)
    {
        counts[c]++;
    }

    int characterCount = 0;

    for (auto word: words)
    {        
        auto temp = counts;
        bool goodWord = true;
        for (auto c: word)
        {
            if (temp.find(c) == temp.end())
            {
                goodWord = false;
                break;
            }
            else
            {
                temp[c]--;
                if (temp[c] == 0)
                {
                    temp.erase(c);
                }
            }
        }

        if (goodWord)
        {
            characterCount += word.size();
        }
    }

    return characterCount;
}

// time complexity: O(n * k + m), where m is size of char, n is size of words and k is size of average word
// space complexity: O(m * n), where m is size of char, n is number of words
int countCharacters_PW2(std::vector<std::string>& words, std::string chars)
{
    std::vector<int> counts(26);
    for (auto c: chars)
    {
        counts[c - 'a']++;
    }

    int characterCount = 0;
    for (auto word: words)
    {        
        std::vector<int> tmp = counts;
        bool goodWord = true;
        for (auto c: word)
        {
            if (--tmp[c - 'a'] < 0)
            {
                goodWord = false;
                break;
            }
        }

        if (goodWord)
        {
            characterCount += word.size();
        }
    }

    return characterCount;
}

int countCharacters(std::vector<std::string>& words, std::string chars)
{
    return countCharacters_PW2(words, chars);
}

std::string sortString(std::string s)
{
    std::string result;
    std::sort(s.begin(), s.end());
    int i = 0;
    int j = s.size() - 1;
    int k = i + 1;

    while (result.size() != s.size())
    {
        // smallest character from s
        result += s[i];
        i++;
        while (k != s.size() && s[k] == s[i])
        {
            k++;
        }

        int l = j;
        while (l >= 0 && s[l] == s[j])
        {
            l--;
        }
        result += s[k];
        k++;
        result += s[j];
        j--;
        result += s[l];
        l--;
    }

    return result;
}

std::string gcdOfStrings(std::string str1, std::string str2)
{
    return "";
}

// space complexity: O(n)
// time complexity: O(n)
bool isIsomorphic(std::string s, std::string t)
{
    if (s.size() != t.size())
    {
        return false;
    }

    std::unordered_map<char, char> myMap;
    for (int i = 0; i < s.size(); ++i)
    {
        if (myMap.find(t[i]) == myMap.end())
        {
            myMap[t[i]] = s[i];
        }
        else if (myMap[t[i]] != s[i])
        {
            return false;
        }

        t[i] = s[i];
    }

    std::set<int> chars;
    for (auto p: myMap)
    {
        if (chars.find(p.second) == chars.end())
        {
            chars.insert(p.second);
        }
        else
        {
            return false;
        }
    }

    return t == s;
}

// time complexity: O(n)
// space complexity: O(1)
std::vector<std::string> findWords(std::vector<std::string>& words)
{
    std::string row1 = "qwertyuiop";
    std::string row2 = "asdfghjkl";
    std::string row3 = "zxcvbnm";
    
    std::vector<std::string> wordsInOneRow;
    for (auto word: words)
    {
        std::set<int> rows;
        for (auto c: word)
        {
            if (row1.find(std::tolower(c)) != std::string::npos)
            {
                rows.insert(1);
            }
            else if (row2.find(std::tolower(c)) != std::string::npos)
            {
                rows.insert(2);
            }
            else if (row3.find(std::tolower(c)) != std::string::npos)
            {
                rows.insert(3);
            }
        }

        if (rows.size() == 1)
        {
            wordsInOneRow.push_back(word);
        }
    }

    return wordsInOneRow;
}

// time complexity: O(n)
// space complexity: O(1)
int balancedStringSplit(std::string s)
{
    int count = 0;
    int numStr = 0;

    for (int i = 0; i < s.size(); ++i)
    {
        if (s[i] == 'L') 
        {
            count++;
        }
        else
        {
            count--;
        }

        if (!count)
        {
            numStr++;
            count = 0;
        }
    }

    return numStr;
}

// time complexity: O(n)
// space complexity: O(1)
std::string toLowerCase(std::string str)
{
    std::string result;
    std::transform(str.begin(), str.end(), std::back_inserter(result), [](char a) {
        return std::tolower(a);
    });
    return result;
}

std::string removeOuterParentheses(std::string S)
{
    std::stack<char> st;
    std::string result = "";
    std::string curResult = "";
    int i = 0;
    while (i != S.size())
    {
        if (S[i] == '(')
        {
            st.push(S[i]);
            result += curResult;
            curResult = "";
        }
        else
        {
            st.pop();
            if (!st.empty())
            {
                curResult += "(";
                curResult += ")";
            }
        }
        ++i;
    }

    result += curResult;
    return result;
}

// time complexity: O(n)
// space complexity: O(1)
std::string truncateSentence(std::string s, int k)
{
    std::string truncated = "";
    int numWords = 0;
    bool inWord = true;
    for (int i = 0; i < s.size(); ++i)
    {
        if (inWord && s[i] == ' ')
        {
            inWord = false;
            numWords++;

            if (numWords == k) break;
        }
        else if (!inWord && isalpha(s[i]))
        {
            inWord = true;
        }

        truncated += s[i];
    }
    
    return truncated;
}

// time complexity: O(n)
// space complexity: O(n)
int uniqueMorseRepresentations(std::vector<std::string>& words)
{
    std::vector<std::string> codes = 
        {".-","-...","-.-.","-..",".",
         "..-.","--.","....","..",".---",
         "-.-",".-..","--","-.","---",".--.",
         "--.-",".-.","...","-","..-","...-",
         ".--","-..-","-.--","--.."};

    std::unordered_set<std::string> reps;
    for (auto word: words)
    {
        std::string rep = "";
        for (auto c: word)
        {
            rep += codes[c - 'a'];
        }
        reps.insert(rep);
    }
    return reps.size();
}

// time complexity: O(1)
// space complexity: O(1)
bool squareIsWhite(std::string coordinates)
{
    return !(((coordinates[0] - 'a') % 2) ^ (coordinates[1] - '1' + 1) % 2);
}

// time complexity: O(n)
// space complexity: O(1)
std::string mergeAlternately(std::string word1, std::string word2)
{
    std::string result;
    int i = 0;
    while (i < word1.size() || i < word2.size())
    {
        std::string a = i < word1.size() ? word1.substr(i, 1) : "";
        std::string b = i < word2.size() ? word2.substr(i, 1) : "";
        result += a;
        result += b;
        i++;
    }

    return result;
}

// time complexity: O(n)
// space complexity: O(1)
bool judgeCircle(std::string moves)
{
    int h = 0;
    int v = 0;

    for (int i = 0; i < moves.size(); ++i)
    {
        switch(moves[i])
        {
            case 'U':
                v++;
                break;
            case 'D':
                v--;
                break;
            case 'L':
                h--;
                break;
            case 'R':
                h++;
                break;
        }
    }

    return h == 0 && v == 0;
}

// time complexity: O(n)
// space complexity: O(k)
std::string reverseWords_PW1(std::string s)
{
    std::string result = "";
    std::string cur = "";
    for (int i = 0; i < s.size(); ++i)
    {
        if (s[i] == ' ')
        {
            result += cur;
            result += ' ';
            cur = "";
        }
        else
        {
            cur = s[i] + cur;
        }
    }

    result += cur;

    return result;
}

// time complexity: O(n)
// space complexity: O(1)
std::string reverseWords_PW2(std::string s)
{
    int j = 0, k = 0;
    for (int i = 0; i < s.size();)
    {
        if (s[i] != ' ')
        {
            k++;
            i++;
        }
        else
        {
            while (j < k)
            {
                std::swap(s[j++], s[--k]);
            }
            while (s[i] == ' ' && i < s.size())
            {
                ++i;
            }
            j = k = i;
        }
    }

    while (j < k)
    {
        std::swap(s[j++], s[--k]);
    }

    return s;
}

std::string reverseWords(std::string s)
{
    return reverseWords_PW2(s);
}

// time complexity: O(n + n log n)
// space complexity: O(n)
std::vector<int> shortestToChar(std::string s, char c)
{
    std::vector<int> dists;
    std::vector<int> occurrences;
    for (int i = 0; i < s.size(); ++i)
    {
        if (s[i] == c)
        {
            occurrences.push_back(i);
        }
    }

    for (int i = 0; i < s.size(); ++i)
    {
        auto upper = std::upper_bound(occurrences.begin(), occurrences.end(), i);
        if (upper == occurrences.end())
        {
            dists.push_back(i - occurrences[occurrences.size() - 1]);
        }
        else if (upper == occurrences.begin())
        {
            dists.push_back(occurrences[0] - i);
        }
        else
        {
            dists.push_back(std::min(*upper-i, i - *(upper - 1)));
        }
    }

    return dists;
}

// time complexity: O(n)
// space complexity: O(n)
int numUniqueEmails(std::vector<std::string>& emails)
{
    std::set<std::string> uniqueEmails;
    for (auto email: emails)
    {
        std::string actualEmail = "";
        bool seenAmp = false;
        bool seenPlus = false;
        for (auto c: email)
        {
            if (c == '@')
            {
                seenAmp = true;
            }
            else if (!seenAmp && seenPlus)
            {
                continue;
            }
            else if (!seenAmp && !seenPlus && c == '.')
            {
                continue;
            }
            else if (!seenAmp && !seenPlus && c == '+')
            {
                seenPlus = true;
                continue;
            }

            actualEmail += c;
        }

        uniqueEmails.insert(actualEmail);
    }

    return uniqueEmails.size();
}

// time complexity: O(n)
// space complexity: O(1)
std::string removeDuplicates(std::string S)
{
    std::string newStr;
    while (!S.empty())
    {
        char c = S[0];
        int count = 1;
        for (int i = 1; i < S.size(); ++i)
        {
            if (S[i] != c)
            {
                if (count == 1)
                {
                    newStr += c;
                }

                c = S[i];
                count = 1;
            }
            else if (S[i] == c)
            {
                count++;

                if (count == 3)
                {
                    c = S[i];
                    count = 1;
                }
            }
        }

        if (count == 1)
        {
            newStr += c;
        }

        if (S == newStr)
        {
            break;
        }

        S = newStr;
        newStr = "";
    }

    return newStr;
}

// time complexity: O(n)
// space complexity: O(1)
bool checkIfPangram(std::string sentence)
{
    int arr[26] = {0};
    for (auto c: sentence)
    {
        arr[c - 'a']++;
    }

    for (auto el: arr)
    {
        if (!el)
        {
            return false;
        }
    }

    return true;
}

// time complexity: O(n)
// space complexity: O(1)
bool canConstruct(std::string ransomNote, std::string magazine)
{
    std::vector<int> rn_count(26);
    std::vector<int> mag_count(26);

    for (auto c: ransomNote)
    {
        rn_count[c - 'a']++;
    }

    for (auto c: magazine)
    {
        mag_count[c - 'a']++;
    }

    for (size_t i = 0; i < 26; ++i)
    {
        if (rn_count[i] > mag_count[i])
        {
            return false;
        }
    }

    return true;
}

// time complexity: O(n)
// space complexity: O(1)
int maxNumberOfBalloons(std::string text)
{
    std::string target = "balloon";
    std::vector<int> count1(26);
    std::vector<int> count2(26);
    for (int i = 0; i < target.size(); ++i)
    {
        count1[target[i] - 'a']++;
    }

    for (int i = 0; i < text.size(); ++i)
    {
        count2[text[i] - 'a']++;
    }

    int maxNum = 0;
    int minDiff = std::numeric_limits<int>::max();
    for (int i = 0; i < 26; ++i)
    {
        if (!count1[i])
        {
            continue;
        }
        else if (count2[i] < count1[i])
        {
            return 0;
        }
        else if (count2[i] == count1[i])
        {
            minDiff = 1;
            continue;
        }
        else if (count2[i] > count1[i])
        {
            minDiff = std::min(minDiff, count2[i] / count1[i]);
        }
    }

    return minDiff;
}

// time complexity: O(n)
// space complexity: O(1)
int maxLengthBetweenEqualCharacters(std::string s)
{
    std::vector<int> idx(26);
    int maxLength = -1;
    for (int i = 0; i < s.size(); ++i)
    {
        if (idx[s[i] - 'a'] == 0)
        {
            idx[s[i] - 'a'] = i + 1;
            continue;
        }
        else
        {
            maxLength = std::max(maxLength, i - idx[s[i] - 'a']);
        }
    }

    return maxLength;
}

// time complexity: O(n)
// space complexity: O(1)
std::string replaceDigits(std::string s)
{
    std::string result;
    for (int i = 0; i < s.size(); ++i)
    {
        if (i % 2 == 0)
        {
            result += s[i];
        }
        else
        {
            result += s[i - 1] + s[i] - '1' + 1;
        }
    }

    return result;
}

// time complexity: O(n)
// space complexity: O(n)
std::string mostCommonWord(std::string paragraph, std::vector<std::string>& banned)
{
    std::unordered_map<std::string, int> counts;
    std::set<std::string> words;
    for (auto b: banned)
    {
        words.insert(b);
    }

    std::string curWord = "";
    size_t index = 0;
    while (index < paragraph.size())
    {
        if (!isalpha(paragraph[index]))
        {
            if (!curWord.empty() && words.find(curWord) == words.end())
            {
                std::string lower = "";
                for (auto c: curWord)
                {
                    lower += std::tolower(c);
                }
                ++counts[lower];
            }

            curWord = "";
        }
        else
        {
            curWord += paragraph[index]; 
        }
        index++;
    }

    if (!curWord.empty() && words.find(curWord) == words.end())
    {
        std::string lower = "";
        for (auto c: curWord)
        {
            lower += std::tolower(c);
        }
        ++counts[lower];
    }

    int maxCount = -1;
    std::string mostCommon = "";
    for (auto pair: counts)
    {
        if (pair.second > maxCount || (pair.second == maxCount && pair.first < mostCommon))
        {
            mostCommon = pair.first;
            maxCount = pair.second;
        }
    }

    return mostCommon;
}

// time complexity: O(n)
// space complexity: O(1)
std::string reverseOnlyLetters(std::string s)
{
    int i = 0, j = s.size() - 1;
    while (i < j)
    {
        if (!isalpha(s[i]))
        {
            ++i;
            continue;
        }
        else if (!isalpha(s[j]))
        {
            --j;
            continue;
        }
        std::swap(s[i], s[j]);
        ++i;
        --j;
    }
    return s;
}

std::vector<std::string> stringMatching(std::vector<std::string>& words)
{
    return {};
}

// time complexity: O(n * w log w)
// space complexity: O(n)
std::vector<std::vector<std::string>> groupAnagrams(std::vector<std::string>& strs)
{
    std::unordered_map<std::string, std::vector<std::string>> anagrams;
    std::vector<std::vector<std::string>> result;
    for (size_t i = 0; i < strs.size(); ++i)
    {
        auto sorted = strs[i];
        std::sort(sorted.begin(), sorted.end());
        anagrams[sorted].push_back(strs[i]);
    }

    for (auto pair: anagrams)
    {
        result.push_back(pair.second);
    }

    return result;
}

// time complexity: O(n log n)
// space complexity: O(n)
std::string frequencySort(std::string s)
{
    std::map<char, int> counts;
    for (int i = 0; i < s.size(); ++i)
    {
        ++counts[s[i]];
    }

    std::multimap<int, char> countsR;
    for (auto pair: counts)
    {
        countsR.insert({pair.second, pair.first});
    }

    std::string result;
    for (auto it = countsR.rbegin(); it != countsR.rend(); it++)
    {
        result += std::string(it->first, it->second);
    }

    return result;
}

// time complexity: O(n)
// space complexity: O(1)
std::string intToRoman(int num)
{
    std::string result;
    std::vector<std::pair<int, std::string>> numerals =
    {
        { 1000, "M" },
        { 900, "CM" },
        { 500, "D"},
        { 400, "CD"},
        { 100, "C"},
        { 90, "XC"},
        { 50, "L"},
        { 40, "XL"},
        { 10, "X"},
        { 9, "IX"},
        { 5, "V"},
        { 4, "IV"},
        { 1, "I"}
    };

    while (num)
    {
        for (auto pair: numerals)
        {
            if (num >= pair.first)
            {
                result += pair.second;
                num -= pair.first;
                break;
            }
        }
    }

    return result;
}