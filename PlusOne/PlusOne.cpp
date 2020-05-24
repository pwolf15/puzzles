#include <vector>
#include <iostream>
#include <assert.h>
#include <sstream>
#include <string>
#include <iterator>
#include <algorithm>

using namespace std;
class Solution
{
public:
    vector<int> plusOne(vector<int> &digits)
    {
        return mostEfficient(digits);
    }

private:

    vector<int> mostEfficient(vector<int> &digits)
    {
        for (int i=digits.size(); i--; digits[i] = 0)
        {
            std::cout << digits[i] << std::endl;
            if (digits[i]++ < 9)
                return digits;
        }

        digits[0]++;
        digits.push_back(0);
        return digits;
    }

    vector<int> memEfficientPlusOne(vector<int> &digits)
    {
        int carry = 1;
        int i = digits.size() - 1;

        // iterate over each digit, add carry at a time
        while (i >= 0)
        {
            if (digits[i] == 9 && carry)
            {
                digits[i] = 0;
                carry = 1;
            }
            else
            {
                digits[i] += carry;
                carry = 0;
            }

            --i;
        }

        if (carry)
        {
            // carry only ever 1
            digits[0] = 1;
            digits.push_back(0);
        }

        return digits;
    }

    vector<int> basicPlusOne(vector<int> &digits)
    {
        std::vector<int> results;
        int carry = 1;
        int i = digits.size() - 1;

        // iterate over each digit, add carry at a time
        while (i >= 0)
        {
            auto result = digits[i] + carry;
            carry = result / 10;
            result %= 10;
            --i;
            results.push_back(result);
        }

        if (carry)
        {
            results.push_back(carry);
        }

        std::reverse(results.begin(), results.end());

        return results;
    }
};

bool equals(const vector<int> a, const vector<int> b)
{
    bool equal = true;

    if (a.size() != b.size())
    {
        return false;
    }

    for (size_t i = 0; i < a.size(); ++i)
    {
        if (a[i] != b[i])
            equal = false;
    }

    return equal;
}

int main()
{

    Solution sol;

    const vector<vector<int>> tests = {
        {4, 3, 2, 1},
        {9, 9, 9},
        {9, 8, 7, 6, 5, 4, 3, 2, 1, 0}};

    const vector<vector<int>> expected = {
        {4, 3, 2, 2},
        {1, 0, 0, 0},
        {9, 8, 7, 6, 5, 4, 3, 2, 1, 1}};

    int i = 0;
    for (auto test : tests)
    {
        auto soln = sol.plusOne(test);
        assert(equals(expected[i], soln));
        std::cout << "Test " << i << " passed.\n";
        i++;
    };

    return 0;
}