#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>
#include <unordered_map>

class Solution
{
public:
    std::vector<std::vector<int>> threeSum(std::vector<int> &nums)
    {
        return threeSum_sorted(nums);
    }

    std::vector<std::vector<int>> threeSum_bruteForce(std::vector<int> &nums)
    {
        std::vector<std::vector<int>> sols;
        std::sort(nums.begin(), nums.end());
        for (int i = 0; i < nums.size(); i++)
        {
            for (int j = i + 1; j < nums.size(); j++)
            {
                int result = nums[i] + nums[j];
                for (int k = j + 1; k < nums.size(); k++)
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

    std::vector<std::vector<int>> threeSum_sorted(std::vector<int>& nums)
    {
        std::vector<std::vector<int>> triples;

        if (nums.size() < 3)
        {
            return triples;
        }

        std::sort(nums.begin(), nums.end());
        int size = nums.size();
        int prev = nums[0] - 1;
        for (int i = 0; i < size; i++)
        {
            // std::cout << i << std::endl;

            if (nums[i] == prev)
            {
                continue;
            }

            int target      = -nums[i];

            int first       = i + 1;
            if (first >= size)
            {
                break;
            }
            int prevFirst   = nums[first] - 1;
            int last        = nums.size() - 1;
            int prevLast    = nums[last] + 1;

            while (first < last)
            {
                // std::cout << "first, " << first << ", last, " << last << std::endl;
                if (first >= size || last < 0)
                {
                    break;
                }

                if (prevFirst == nums[first])
                {
                    first++;
                    continue;
                }
                if (prevLast == nums[last])
                {
                    last--;
                    continue;
                }

                int sum = nums[first] + nums[last];
                if (sum < target)
                {
                    first++;
                }
                else if (sum > target)
                {
                    last--;
                }
                else
                {
                    triples.push_back({ nums[i], nums[first], nums[last], });

                    prevFirst = nums[first];
                    prevLast = nums[last];
                }
            }

            prev = nums[i];
        }

        return triples;
    }
};

int main()
{
    Solution sol;
    std::vector<int> inCells = {-1, 0, 1, 2, -1, -4};
    auto result = sol.threeSum(inCells);
    // for (auto triplet : result)
    // {
    //     std::cout << "Solution!" << std::endl;

    //     for (auto member : triplet)
    //     {
    //         std::cout << member << ", ";
    //     }

    //     std::cout << "\n";
    // }

    inCells = {};

    sol.threeSum(inCells);

    inCells = {0};

    sol.threeSum(inCells);

    inCells = {1,2,-2,-1};

    result = sol.threeSum(inCells);
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