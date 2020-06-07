#include <vector>
#include <iostream>
#include <assert.h>
#include <limits>
#include <algorithm>
#include <numeric>
#include <map>

using namespace std;

class Solution
{
public:
    int change(int amount, vector<int> &coins)
    {
        vector<int> dp(amount + 1);
        dp[0] = 1;
        for (auto c : coins)
            for (auto j = c; j <= amount; ++j)
                dp[j] += dp[j - c];
        return dp[amount];
    }

private:
};

int main()
{

    Solution sol;
    vector<int> coins = {1, 2, 5};
    std::cout << sol.change(5, coins) << std::endl;

    return 0;
}