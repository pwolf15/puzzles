#include <vector>
#include <iostream>
#include <assert.h>
#include <limits>
#include <algorithm>
#include <set>

using namespace std;

class Solution {
public:
    int singleNumber(vector<int>& nums) {
        
        std::set<int> nums2;
        for (int i = 0; i < nums.size(); ++i)
        {
            auto pos = nums2.find(nums[i]);
            if (pos != nums2.end())
            {
                nums2.erase(*pos);
            }
            else
            {
                nums2.insert(nums[i]);
            }
        }

        return *nums2.begin();
    }
};

int main()
{

    Solution sol;

    const std::vector<std::vector<int>> tests = {
        {2,2,1},
        {4,1,2,1,2},
    };

    const std::vector<int> expected = {
       1,
       4,
    };

    int i = 0;
    for (auto test: tests)
    {
        auto soln = sol.singleNumber(test);
        assert(soln == expected[i]);
        std::cout << "Test " << i << " passed.\n";
        i++;
    };

    return 0;
}