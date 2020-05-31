#include <vector>
#include <iostream>
#include <assert.h>

using namespace std;


class Solution {
public:
    int maxProfit(vector<int>& prices) {
        return efficientSearch(prices);
    }
private:
    int bruteForce(vector<int>& prices) {
                
        int maxProfit = 0;
        if (prices.empty())
        {
            return maxProfit;
        }

        for (int i = 0; i < prices.size() - 1; ++i)
        {
            for (int j = i + 1; j < prices.size(); ++j)
            {
                int profit = prices[j] - prices[i];
                if (profit > maxProfit)
                {
                    maxProfit = profit;
                }
            }
        }

        return maxProfit;
    }

    int efficientSearch(vector<int>& prices) {
                
        int maxProfit = 0;
        int profit = 0;
        if (prices.empty() || prices.size() == 1)
        {
            return maxProfit;
        }

        int left    = 0;
        int right   = 1;
        int i = 0;
        int j = 1;
        while (true)
        {
            if ((prices[i] < prices[left]))
            {
                profit = prices[right] - prices[left];
                maxProfit = profit > maxProfit ? profit : maxProfit;
                left = i;
                right = j;
            }
                

            if (prices[j] >= prices[right])
            {
                profit = prices[right] - prices[left];
                maxProfit = profit > maxProfit ? profit : maxProfit;
                right = j;
            }
                

            i++;
            j++;

            if (j >= prices.size())
                break;
        }

        profit = prices[right] - prices[left];
        maxProfit = profit > maxProfit ? profit : maxProfit; 
        if (maxProfit < 0)
            maxProfit = 0;

        return maxProfit;
    }
};

int main()
{

    Solution sol;

    const std::vector<std::vector<int>> tests = {
        { 7,1,5,3,6,4 },
        { 7,6,4,3,1 },
        {1,2},
        {},
        {1},
        {2,1,2,1,0,1,2}
    };

    const std::vector<int> expected = {
        5,
        0,
        1,
        0,
        0,
        2
    };

    int i = 0;
    for (auto test: tests)
    {
        auto soln = sol.maxProfit(test);
        assert(soln == expected[i]);
        std::cout << "Test " << i << " passed.\n";
        i++;
    };

    return 0;
}