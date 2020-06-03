#include <vector>
#include <iostream>
#include <assert.h>

using namespace std;

class Solution {
public:
    int addDigits(int num) {
        
        while (true)
        {
            auto result = num / 10;
            if (!result)
            {
                return result;
            }
            else
            {
                auto sum = 0;
                auto carry = 0;
                auto factor = 10;
                while (carry)
                {
                    // 38
                    sum += num % factor;
                    factor *= 10;
                }
            }
        }
    }
};

int main()
{

    Solution sol;

    const std::vector<int> tests = {
        38,
    };

    const std::vector<int> expected = {
        2,
    };

    int i = 0;
    for (auto test: tests)
    {
        auto soln = sol.addDigits(test);
        assert(soln == expected[i]);
        std::cout << "Test " << i << " passed.\n";
        i++;
    };

    return 0;
}