#include <vector>
#include <iostream>
#include <assert.h>
#include <sstream>
#include <string>
#include <iterator>
#include <algorithm>

using namespace std;
class Solution {
public:
    vector<int> plusOne(vector<int>& digits) {
        
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
        { 4, 3, 2, 1 },
        { 9, 9, 9 }
    };

    const vector<vector<int>> expected = {
        { 4, 3, 2, 2 },
        { 1, 0, 0, 0 }
    };

    int i = 0;
    for (auto test: tests)
    {
        auto soln = sol.plusOne(test);
        assert(equals(expected[i], soln));
        std::cout << "Test " << i << " passed.\n";
        i++;
    };

    return 0;
}