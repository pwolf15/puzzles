#include <vector>
#include <iostream>
#include <assert.h>
#include <limits>
#include <queue>
#include <cmath>
#include <algorithm>

using namespace std;

class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {
        
        auto found = std::find(nums.begin(), nums.end(), target);
        if (found == nums.end()) 
        {
            found = std::upper_bound(nums.begin(), nums.end(), target);
            return found - nums.begin();
        }
        else 
        {
            return found - nums.begin();
        }
    }
};

int main()
{

    Solution sol;

    const std::vector<std::pair<std::vector<int>, int>> tests = {
        {{1,3,5,6}, 5},
        {{1,3,5,6}, 2},
        {{1,3,5,6}, 7},
        {{1,3,5,6}, 0},
    };

    const std::vector<int> expected = {
        2,
        1,
        4,
        0,
    };

    int i = 0;
    for (auto test : tests)
    {
        auto soln = sol.searchInsert(test.first, test.second);
        assert(soln == expected[i]);
        std::cout << "Test " << i << " passed.\n";
        i++;
    };

    return 0;
}