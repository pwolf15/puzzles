#include <vector>
#include <iostream>
#include <assert.h>
#include <sstream>
#include <string>
#include <iterator>
#include <algorithm>

using namespace std;

class Solution {
public:
    int numJewelsInStones(string J, string S) {
        
        int jewelCount = 0;
        int jewelsIndex = 0;
        int stonesIndex = 0;

        std::sort(J.begin(), J.end());
        std::sort(S.begin(), S.end());

        while (true)
        {
            if (jewelsIndex >= J.size() || stonesIndex >= S.size())
            {
                // reached end of jewels or stones, break
                break;
            }
            else if (J[jewelsIndex] == S[stonesIndex])
            {
                // found jewel, increment stones index
                jewelCount++;
                stonesIndex++;
            }
            else if (J[jewelsIndex] < S[stonesIndex])
            {
                // jewel < stone alphabetically, increment jewel index
                jewelsIndex++;
            }
            else if (J[jewelsIndex] > S[stonesIndex])
            {
                // jewel > stone alphabetically, increment stones index
                stonesIndex++;
            }
        }

        return jewelCount;
    }
};

int main()
{

    Solution sol;

    const std::vector<std::vector<std::string>> tests = {
        { "aA", "aAAbbbb" },
        { "z", "ZZ" },
        { "a", "a"},
    };

    const std::vector<int> expected = {
        3,
        0,
        1
    };

    int i = 0;
    for (auto test : tests)
    {
        auto soln = sol.numJewelsInStones(test[0], test[1]);
        std::cout << "Soln: " << soln << std::endl;
        assert(expected[i] == soln);
        std::cout << "Test " << i << " passed.\n";
        i++;
    };

    return 0;
}