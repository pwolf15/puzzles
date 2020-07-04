#include <vector>
#include <iostream>
#include <assert.h>
#include <limits>
#include <algorithm>
#include <regex>
#include <map>
#include <queue>
#include <set>

using namespace std;

class Solution {
public:
    int nthUglyNumber(int n) {
        
        int i = 0;
        int cur = 1;
        uglyNumbers.insert(1);

        int max2nd = std::numeric_limits<int>::max() / 2;
        int max3rd = std::numeric_limits<int>::max() / 3;
        int max5th = std::numeric_limits<int>::max() / 5;
        while (true)
        {
            cur = *(uglyNumbers.begin());
            uglyNumbers.erase(cur);
            i++;
            std::cout << cur << std::endl;
            if (i == n)
            {
                break;
            }

            if (cur <= max2nd && visited.find(cur * 2) == visited.end())
            {
                uglyNumbers.insert(cur * 2);
                visited.insert(cur * 2);
            }

            if (cur <= max3rd && visited.find(cur * 3) == visited.end())
            {
                uglyNumbers.insert(cur * 3);
                visited.insert(cur * 3);
            }

            if (cur <= max5th && visited.find(cur * 5) == visited.end())
            {
                uglyNumbers.insert(cur * 5);
                visited.insert(cur * 5);
            }
        }

        return cur;
    }
private:
    std::set<int> uglyNumbers;
    std::set<int> visited;
};

int main()
{

    Solution sol;
    
    // 1 + 2 + 3 + 4 = 12
    // 13 - 10 = 3 / 1
    // { 3, 3, 3 }
    // 
    std::vector<int> nums = {1, 4, 1, 4, 2, 1, 3, 5, 6};
    std::cout << "\n";
    std::cout << sol.nthUglyNumber(1407) << std::endl;

    return 0;
}