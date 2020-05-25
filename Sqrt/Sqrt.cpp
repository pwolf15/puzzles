#include <vector>
#include <iostream>
#include <assert.h>
#include <limits>

using namespace std;

class Solution {
public:
    int mySqrt(int x) {
        
        int result = 0;
        for (int i = 0; i <= x / 2 + 1; i++)
        {
            long m = (long)i * (long)i;
            if (m == x)
            {
                result = i;
            }
            else if (m > x)
            {
                result = i - 1;
                break;
            }
        }

        std::cout << "Result: " << result << std::endl;

        return result;
    }

private:
};

int main()
{

    Solution sol;

    const std::vector<int> tests = {
        4,
        9,
        8,
        0,
        225,
        65536,
        65537,
        2147395600
    };

    const std::vector<int> expected = {
       2,
       3,
       2,
       0,
       15,
       256,
       256,
       289398
    };

    int i = 0;
    for (auto test: tests)
    {
        auto soln = sol.mySqrt(test);
        assert(soln == expected[i]);
        std::cout << "Test " << i << " passed.\n";
        i++;
    };

    return 0;
}