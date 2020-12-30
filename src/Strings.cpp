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

// Returns the index of the first character of the substring if found, -1 otherwise.
int findStr_RobinKarp(const std::string& s, const std::string& t)
{
    if (std::size(s) > std::size(t)) {
        return -1; // s is not a substring of t
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