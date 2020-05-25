#include <vector>
#include <iostream>
#include <assert.h>
#include <limits>
#include <map>

using namespace std;

class Solution
{
public:
    Solution()
    {
        stepSizes[0] = 1;
        stepSizes[1] = 1;
        stepSizes[2] = 2;
        stepSizes[3] = 3;
    }

    int climbStairs(int n)
    {
        if (stepSizes[n])
        {
            return stepSizes[n];
        }
        else
        {
            auto result = climbStairs(n - 1) + climbStairs(n - 2);
            stepSizes[n] = result;
            return result;
        }
    }

private:
    std::map<int, int> stepSizes;
};

int main()
{
    Solution sol;

    const std::vector<int> tests = {
        2,
        3,
        4,
        5,
        6,
        7,
        8,
        9,
    };

    const std::vector<int> expected = {
        2,
        3,
        5,
        8,
        13,
        21,
        34,
        55,
    };

    int i = 0;
    for (auto test : tests)
    {
        auto soln = sol.climbStairs(test);
        std::cout << "Soln: " << soln << std::endl;
        assert(soln == expected[i]);
        std::cout << "Test " << i << " passed.\n";
        i++;
    };

    return 0;
}

