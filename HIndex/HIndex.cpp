#include <vector>
#include <iostream>
#include <assert.h>
#include <limits>
#include <algorithm>
#include <regex>
#include <map>

using namespace std;

class Solution {
public:
    int hIndex(vector<int>& citations) {
        
        indices.clear();

        if (citations.empty())
        {
            return 0;
        }
        
        for (auto num: citations)
        {
            auto it = indices.find(num);
            if (it != indices.end())
            {
                it->second++;
            }
            else
            {
                indices.insert({ num, 1 });
            }
        }

        int total = 0;
        int hIndex = 0;

        std::map<int,int>::reverse_iterator rit;
        for (rit = indices.rbegin(); rit != indices.rend(); rit++)
        {
            if (total > rit->first)
            {
                break;
            }
            else
            {
                total += rit->second;

                if (total > rit->first)
                {
                    total = rit->first;
                    break;
                }
            }
        }
        
        return total;
    }
private:
    std::map<int, int> indices;
};


int main()
{

    Solution sol;
    
    // 1 + 2 + 3 + 4 = 12
    // 13 - 10 = 3 / 1
    // { 3, 3, 3 }
    // 
    std::vector<int> nums = {1, 4, 1, 4, 2, 1, 3, 5, 6};
    std::cout << sol.hIndex(nums) << std::endl;
    nums = { 11, 15 };
    std::cout << sol.hIndex(nums) << std::endl;
    nums = { 0 };
    std::cout << sol.hIndex(nums) << std::endl;
    nums = { 1, 1 };
    std::cout << sol.hIndex(nums) << std::endl;
    nums = { 4,4,0,0 };
    std::cout << sol.hIndex(nums) << std::endl;
    nums = {1,7,9,4};
    std::cout << sol.hIndex(nums) << std::endl;

    return 0;
}