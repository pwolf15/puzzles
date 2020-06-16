#include <vector>
#include <iostream>
#include <assert.h>
#include <limits>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<int> largestDivisibleSubset(vector<int>& nums) {
        // for (int i = 0; i < nums.size(); ++i)
        // {
        //     for 
        // }
        //     q = std::max(q, prices[i] + largestDivisibleSubset(nums.size());
    }

};

int main()
{

    Solution sol;
    vector<int> nums = { 1, 2, 3, 4, 5, 6};
    auto subset = sol.largestDivisibleSubset(nums);
    for (auto n: subset)
    {
        std::cout << n << std::endl;
    }

    return 0;
}