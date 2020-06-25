#include <vector>
#include <iostream>
#include <assert.h>
#include <limits>
#include <queue>
#include <cmath>
#include <unordered_map>

#include "Trees.hpp"

using namespace std;

class Solution {
public:
    int numTrees(int n) {
        // Base case 
        if (n <= 1) return 1; 
    
        // catalan(n) is sum of catalan(i)*catalan(n-i-1) 
        unsigned long int res = 0; 
        for (int i=0; i<n; i++) 
        {
            auto opA = 0;
            auto opB = 0;
            if (mem.find(i) == mem.end())
            {
                opA = numTrees(i);
                mem.insert({i, opA});
            }
            else
            {
                opA = mem.find(i)->second;
            }
            
            if (mem.find(n - i - 1) == mem.end())
            {
                opB = numTrees(n - i - 1);
                mem.insert({n - i - 1, opB});
            }
            else
            {
                opB = mem.find(n - i - 1)->second;
            }

            res += opA * opB;
        }
        
        return res;
    }
private:
    std::unordered_map<int, int> mem;
};

int main()
{

    Solution sol;

    const std::vector<int> tests = {
        3,
        2,
        7,
        13,
    };

    const std::vector<int> expected = {
       5,
       2,
       429,
       742900
    };

    int i = 0;
    for (auto test : tests)
    {
        auto soln = sol.numTrees(test);
        std::cout << soln << std::endl;
        assert(soln == expected[i]);
        std::cout << "Test " << i << " passed.\n";
        i++;
    };

    return 0;
}