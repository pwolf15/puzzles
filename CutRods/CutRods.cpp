#include <vector>
#include <iostream>
#include <assert.h>
#include <limits>
#include <algorithm>

using namespace std;
class Solution {
public:
    int cutRod(vector<int>& prices, int rodLength) {

        if (rodLength == 0)
        {
            return 0;
        }
        int q = -1;
        for (int i = 1; i <= rodLength; ++i)
            q = std::max(q, prices[i] + cutRod(prices, rodLength - i));

        return q;
    }
};

int main()
{

    Solution sol;
    vector<int> prices = {0, 1, 5, 8, 9, 10, 17, 17, 20, 24, 30};
    for (int i = 0; i <= 10; i++)
    {
        std::cout << sol.cutRod(prices, i) << std::endl;
    }

    return 0;
}