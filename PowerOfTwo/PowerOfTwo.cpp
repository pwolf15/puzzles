#include <vector>
#include <iostream>
#include <assert.h>
#include <limits>
#include <algorithm>

using namespace std;

class Solution {
public:
    bool isPowerOfTwo(int n) {
        int cmp = 1;
        int i = 1;
        bool powerOfTwo = false;
        while (i < 32)
        {
           
            if (n == cmp)
            {
              powerOfTwo = true;
                break;
            }
           cmp = 1 << i;
            i++;
        }
        
        return powerOfTwo;
    }
};

int main()
{

    Solution sol;

    const std::vector<int> tests = {
        0,
        1,
        2,
        65536,
        3
    };

    const std::vector<bool> expected = {
       false,
       true,
       true,
       true,
       false,
    };

    int i = 0;
    for (auto test: tests)
    {
        auto soln = sol.isPowerOfTwo(test);
        std::cout << "Solution: " << soln << std::endl;
        std::cout << "Expected: " << expected[i] << std::endl;
        assert(soln == expected[i]);
        std::cout << "Test " << i << " passed.\n";
        i++;
    };

    return 0;
}