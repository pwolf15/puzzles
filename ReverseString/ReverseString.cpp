#include <vector>
#include <iostream>
#include <assert.h>
#include <limits>
#include <algorithm>

using namespace std;

class Solution
{
public:
    void reverseString(vector<char> &s)
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
};

bool equals(vector<char> &a, vector<char> &b)
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
}

int main()
{

    Solution sol;

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

    int i = 0;
    for (auto test : tests)
    {
        sol.reverseString(test);
        assert(equals(expected[i], test));
        std::cout << "Test " << i << " passed.\n";
        i++;
    };

    return 0;
}