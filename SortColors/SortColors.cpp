#include <vector>
#include <iostream>
#include <assert.h>
#include <limits>
#include <queue>
#include <cmath>
#include <algorithm>

using namespace std;

class Solution {
public:
    void sortColors(vector<int>& nums) {
        int numReds = 0;
        int numWhites = 0;
        int numBlues = 0;
        for (auto num: nums)
        {
            if (num == 0)
            {
                numReds++;
            }
            else if (num == 1)
            {
                numWhites++;
            }
            else if (num == 2)
            {
                numBlues++;
            }
        }

        int i = 0;
        for (i = 0; i < numReds; i++)
        {
            nums[i] = 0;
        }
        for (; i < numWhites + numReds; i++)
        {
            nums[i] = 1;
        }
        for (; i < numBlues + numWhites + numReds; i++)
        {
            nums[i] = 2;
        }
    }
};

int main()
{

    Solution sol;

    std::vector<int> test = {2,0,2,1,1,0};

    sol.sortColors(test);

    for (auto c: test)
    {
        std::cout << c << std::endl;
    }
    return 0;
}