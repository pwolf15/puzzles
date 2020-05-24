#include <vector>
#include <iostream>
#include <assert.h>

using namespace std;

class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        
        return maxSubArrayLinear(nums);
    }
    
private:
    
    int maxSubArrayLinear(vector<int>& nums)
    {
        assert(nums.size() > 0);

        // sum: running total for contiguous elements
        // max: current largest sum

        int sum     = nums[0];
        int maxSum  = sum;
        
        for (size_t i = 1; i < nums.size(); i++)
        {
            sum += nums[i];
            sum = std::max(nums[i], sum);
            maxSum = std::max(sum, maxSum);
        }
        
        return maxSum;
    }

    int maxSubArrayDynamic(vector<int> &nums)
    {

    }
};

int main()
{

    Solution sol;

    const std::vector<std::vector<int>> tests = {
        {  1 },
        { -1 },
        { 0  },
        { -2,1,-3,4,-1,2,1,-5,4 }
    };

    const std::vector<int> expected = {
        1,
        -1,
        0,
        6
    };

    int i = 0;
    for (auto test: tests)
    {
        auto soln = sol.maxSubArray(test);
        assert(soln == expected[i]);
        std::cout << "Test " << i << " passed.\n";
        i++;
    };

    return 0;
}