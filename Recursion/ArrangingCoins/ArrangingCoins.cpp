#include <vector>
#include <iostream>
#include <assert.h>
#include <limits>
#include <algorithm>
#include <unordered_map>
#include <iterator>
#include <unordered_set>
#include <math.h>

using namespace std;

class Solution
{
public:
    int arrangeCoins(int n)
    {
        if (n == 1 || n == 0)
        {
            return n;
        }
        return (-1 + floor(sqrt(1.0f + 4.0f * (2.0f * (double)n)))) / 2;
    }
};

int main()
{
    Solution sol;
    std::cout << sol.arrangeCoins(1) << std::endl;
    std::cout << sol.arrangeCoins(8) << std::endl;
    std::cout << sol.arrangeCoins(5) << std::endl;
    std::cout << sol.arrangeCoins(6000) << std::endl;
    std::cout << sol.arrangeCoins(1) << std::endl;
    std::cout << sol.arrangeCoins(1804289383) << std::endl;
    std::cout << sol.arrangeCoins(3) << std::endl;
    std::cout << sol.arrangeCoins(9) << std::endl;

    return 0;
}