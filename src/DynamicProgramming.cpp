#include "DynamicProgramming.hpp"
#include <vector>

// You are climbing a stair case. It takes n steps to reach to the top.
// Each time you can either climb 1 or 2 steps. 
// In how many distinct ways can you climb to the top?
// 2 => 1,1; 2 (2)
// 3 => 1,2; 1,1,1; 2,1 (3)
// 4 => 1,1,1,1; 1,1,2; 1,2,1; 2,1,1; 2,2 (5)


int climbStairs(int n)
{
    std::vector<int> memoized(100, -1);

    for (int i = 1; i <= n; ++i)
    {
        if (i == 1 || i == 0)
        {
            memoized[i] = 1;
        }
        else if (i == 2)
        {
            memoized[i] = 2;
        }
        else
        {
            memoized[i] = memoized[i - 1] + memoized[i - 2];
        }
    }

    return memoized[n];
}