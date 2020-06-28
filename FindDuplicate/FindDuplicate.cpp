#include <vector>
#include <iostream>
#include <assert.h>
#include <limits>
#include <algorithm>
#include <regex>

using namespace std;

class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        
        int sum1 = 0;
        int sum2 = 0;
        int min = std::numeric_limits<int>::max();
        int max = std::numeric_limits<int>::min();

        // real sum
        for (auto num: nums)
        {
            if (num < min)
            {
                min = num;
            }
            if (num > max)
            {
                max = num;
            }
            sum1 += num;
        }

        // expected sum
        for (int i = min; i <= max; i++)
        {
            sum2 += i;
        }

        std::cout << "Expected: " << sum2 << std::endl;
        std::cout << "Real: " << sum1 << std::endl;

        return (sum1 - sum2) / (nums.size() - (max - min + 1));
    }
};


int main()
{

    Solution sol;
    
    // 1 + 2 + 3 + 4 = 12
    // 13 - 10 = 3 / 1
    // { 3, 3, 3 }
    // 
    std::vector<int> nums = {1,3,4,2,2};
    std::cout << sol.findDuplicate(nums) << std::endl;
    nums = {3,1,3,4,2};
    std::cout << sol.findDuplicate(nums) << std::endl;
    nums = { 3, 3, 3 };
    std::cout << sol.findDuplicate(nums) << std::endl;
    nums = {1,4,4,2,4};
    std::cout << sol.findDuplicate(nums) << std::endl;

    return 0;
}