#include <vector>
#include <iostream>
#include <assert.h>
#include <limits>
#include <algorithm>

using namespace std;
class Solution {
public:
    int twoCitySchedCost(vector<vector<int>>& costs) {

        auto cmp = [](const vector<int>& lhs, const vector<int>& rhs)
        {
            return lhs[0] - lhs[1] < rhs[0] - rhs[1];
        };
        sort(costs.begin(), costs.end(), cmp);

        int n = costs.size();
        int total = 0;
        for (int i = 0; i < n; ++i) 
        {
            if (i < n / 2) {
                total += costs[i][0];
            } else {
                total += costs[i][1];
            }
        }

        return total;
    }
};

int main()
{

    Solution sol;

    const std::vector<std::vector<std::vector<int>>> tests = {
        {{10,20},{30,200},{400,50},{30,20}},
        {{259,770},{448,54},{926,667},{184,139},{840,118},{577,469}}
    };

    const std::vector<int> expected = {
       110,
       1859,
    };

    int i = 0;
    for (auto test: tests)
    {
        auto soln = sol.twoCitySchedCost(test);
        std::cout << "Solution: " << soln << std::endl;
        std::cout << "Expected: " << expected[i] << std::endl;
        assert(soln == expected[i]);
        std::cout << "Test " << i << " passed.\n";
        i++;
    };

    return 0;
}