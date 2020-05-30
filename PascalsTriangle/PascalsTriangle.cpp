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
    vector<vector<int>> generate(int numRows)
    {

        vector<vector<int>> result = {};

        if (numRows == 0)
        {
            return result;
        }
        int i = 1;
        while (true)
        {
            if (i == 1)
            {
                result.push_back({1});
                i++;
            }
            else
            {
                std::vector<int> row = {1};
                auto prevRow = result[result.size() - 1];
                for (int i = 1; i < prevRow.size(); i++)
                {
                    if (i-1 >= 0)
                    {
                         row.push_back(prevRow[i] + prevRow[i - 1]);
                    }
                    else
                    {
                        row.push_back(prevRow[i]);
                    }
                    
                   
                }
                row.push_back(1);
                result.push_back(row);
                i++;
            }

            if (i > numRows)
            {
                break;
            }
        }

        return result;
    }
};

int main()
{

    Solution sol;

    const vector<int> tests = {
        1,
        5,
    };

    const vector<vector<vector<int>>> expected = {
        {
            {1},
        },
        {
            {1},
            {1, 1},
            {1, 2, 1},
            {1, 3, 3, 1},
            {1, 4, 6, 4, 1},
        }};

    int i = 0;
    for (auto test : tests)
    {
        auto soln = sol.generate(tests[i]);
        assert(expected[i] == soln);
        std::cout << "Test " << i << " passed.\n";
        i++;
    };

    return 0;
}