#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

class Solution {
public:
    int maxArea(vector<int>& height) {
        
        
        std::vector<int> areas;
        int curMax = 0;
        int leftBound = 0;
        int rightBound = height.size();
        // brute-force == find area between any two pairs
        // O(n^2)
        
        for (int i = 0; i < height.size() - 1; ++i) 
        {
            for (int j = leftBound; j < rightBound; ++j)
            {
                if (((j - leftBound) <= (height[j] - height[leftBound])) && (j - leftBound) > 0)
                {
                    leftBound = j;
                    std::cout << std::endl << "Changing left bound: " << leftBound << ", " << height[j] << std::endl;
                }
                if (((rightBound - j) <= (height[j] - height[rightBound])) && (rightBound - j) >= 0)
                {
                    rightBound = j;
                    std::cout << std::endl << "Changing right bound: " << rightBound << ", " << height[j] << std::endl;
                }
                auto area = std::min(height[i], height[j]) * (j - i);
                curMax = std::max(curMax, area);
            }
        }

        // 
        
        return curMax;
    }
};

int main() 
{
    Solution sol;
    // at 1: distances 1
    // distance between 1
    std::vector<int> heights = {1,8,6,2,5,4,8,3,7};
    std::cout << "Max area: " << sol.maxArea(heights) << "\n";

    return 0;
}

// 1,8,6,2,5,4,8,3,7
// can change leftbound to 8 once I've passed 8, because distance between 1 
// can actually drop 6 too once you pass it 
// 