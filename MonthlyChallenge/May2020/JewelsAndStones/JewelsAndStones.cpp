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
        for (int i = 0; i < S.size(); ++i)
        {
            for (int j = 0; j < J.size(); ++j)
            {
                
            }
        }
    }
};

int main()
{

    Solution sol;

    const std::vector<std::vector<std::string>> tests = {
        { "aA", "aAAbbbb" },
        { "z", "ZZ" }
    };

    const std::vector<int> expected = {
        3,
        0
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