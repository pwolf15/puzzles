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
};

int main()
{

    Solution sol;

    std::vector<int> arr1 = { -2,1,-3,4,-1,2,1,-5,4 };
    std::cout << sol.maxSubArray(arr1) << std::endl;
    return 0;
}