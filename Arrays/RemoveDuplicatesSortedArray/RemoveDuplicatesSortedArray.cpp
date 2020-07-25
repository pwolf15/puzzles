#include <vector>
#include <iostream>
#include <assert.h>
#include <limits>

using namespace std;

class Solution {
public:
    int removeDuplicates(vector<int>& nums) 
    {
        return removeDuplicates_Efficient(nums);
    }

private:

    int removeDuplicates_Efficient(vector<int>& nums)
    {
        // time complexity: O(n) where n is array length
        // space complexity: O(1)

        // keep two points i and j, where i is slow-runner and j
        // is the fast-runner. As long as nums[i] == nums[j], increment j
        // to skip the duplicate.

        // When we encounter nums[j] != nums[i], the duplicate run has ended
        // so we must copy it svalue to nums[i + 1]. i can be incremented and
        // we repeat the same process until i reaches the array end

        if (nums.empty())
        {
            return 0;
        }

        int i = 0;
        for (int j = 1; j < nums.size(); ++j)
        {
            if (nums[j] != nums[i])
            {
                i++;
                nums[i] = nums[j];
            }
        }

        return i + 1;
    }

    int removeDuplicates_PW(vector<int>& nums)
    {
        if (nums.empty())
        {
            return 0;
        }

        int curElement  = nums[0];
        int curLength   = 1;
        for (auto i = 1; i < nums.size(); ++i)
        {
            // only increase size of unique element found
            // relies on sorted precondition
            if (nums[i] != curElement)
            {
                nums[curLength++] = nums[i];
                curElement = nums[i];
            }
        }
        
        return curLength;
    }
};

int main()
{

    Solution sol;

    const std::vector<std::vector<int>> tests = {
        { },
        { 1, 1, 2 },
        { 1, 1, 2, 3, 3},
        { 1 }
    };

    const std::vector<std::pair<int, std::vector<int>>> expected = {
        { 0, { } },
        { 2, { 1, 2 }},
        { 3, { 1, 2, 3}},
        { 1, { 1 }},
    };

    int i = 0;
    for (auto test : tests)
    {
        auto soln = sol.removeDuplicates(test);

        assert(soln == expected[i].first);
        std::cout << "Test " << i << " passed.\n";
        i++;
    };

    return 0;
}