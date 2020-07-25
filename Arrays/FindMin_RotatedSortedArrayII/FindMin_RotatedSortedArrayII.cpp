#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>
#include <unordered_map>

class Solution {
public:
    int findMin(std::vector<int>& nums) {
        
        int cur = nums[0];
        for (auto num: nums)
        {
            if (num < cur)
            {
                cur = num;
            }
            
        }

        return cur;
    }
};

int main()
{
    Solution sol;
    std::vector<int> inCells = {2,2,2,0,1};
    std::cout << sol.findMin(inCells) << std::endl;
    inCells = {1,3,5};
    std::cout << sol.findMin(inCells) << std::endl;
    inCells = {4,5,6,7,0,1,2};
    std::cout << sol.findMin(inCells) << std::endl;

    return 0;
}