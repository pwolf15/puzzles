#include <vector>
#include <iostream>
#include <assert.h>
#include <limits>
#include <algorithm>
#include <unordered_map>

using namespace std;

class Solution {
public:
    int singleNumber(vector<int>& nums) {
        
        std::unordered_map<int, int> numberMap;
        for (auto num: nums)
        {
            if (numberMap.find(num) != numberMap.end())
            {
                numberMap[num]++;
            }
            else
            {
                numberMap[num] = 1;
            } 
        }
        for (auto num: numberMap)
        {
            if (num.second != 3)
            {
                return num.first;
            }
        }
    }
};

int main()
{

    Solution sol;

    const std::vector<std::vector<int>> tests = {
        {2,2,3,2},
        {0,1,0,1,0,1,99},
    };

    const std::vector<int> expected = {
       3,
       99,
    };

    int i = 0;
    for (auto test: tests)
    {
        auto soln = sol.singleNumber(test);
        std::cout << "Soln: " << soln << std::endl;
        assert(soln == expected[i]);
        std::cout << "Test " << i << " passed.\n";
        i++;
    };

    return 0;
}