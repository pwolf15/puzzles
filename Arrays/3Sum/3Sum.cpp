#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>

class Solution
{
public:
    std::vector<std::vector<int>> threeSum(std::vector<int> &nums)
    {

        std::vector<std::vector<int>> sols;
        std::sort(nums.begin(), nums.end());
        for (int i = 0; i < nums.size(); i++)
        {
            for (int j = 1; j < nums.size(); j++)
            {
                int result = nums[i] + nums[j];
                for (int k = 2; k < nums.size(); k++)
                {
                    if (((i != j) && (j != k) && (i != k)) && (result + nums[k]) == 0)
                    {
                        bool found = false;
                        std::vector<int> cur = {nums[i], nums[j], nums[k]};
                        std::sort(cur.begin(), cur.end());
                        for (auto sol : sols)
                        {
                            if ((cur[0] == sol[0]) && (cur[1] == sol[1]) && (cur[2] == sol[2]))
                            {
                                found = true;
                                break;
                            }
                        }

                        if (!found)
                        {
                            sols.push_back(cur);
                        }
                    }
                }
            }
        }

        return sols;
    }
};

int main()
{
    Solution sol;
    std::vector<int> inCells = {-1, 0, 1, 2, -1, -4};
    auto result = sol.threeSum(inCells);
    for (auto triplet : result)
    {
        std::cout << "Solution!" << std::endl;

        for (auto member : triplet)
        {
            std::cout << member << ", ";
        }

        std::cout << "\n";
    }

    return 0;
}