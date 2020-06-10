#include <vector>
#include <iostream>
#include <assert.h>
#include <limits>
#include <map>
#include <cctype>

using namespace std;
class Solution {
public:
    bool isSubsequence(string s, string t) {
        
        if (s.size() > t.size())
        {
            return false;
        }
        else if (s.empty())
        {
            return true;
        }
        else
        {
            if (s[0] == t[0])
            {
                return isSubsequence(s.substr(1), t.substr(1));
            }
            else
            {
                return isSubsequence(s, t.substr(1));
            } 
        }
    }
};

int main()
{
    Solution sol;

    const std::vector<std::vector<std::string>> tests = {
        { "", "" },
        { "a", "" },
        { "a", "a" },
        { "a", "ab"},
        { "abc", "abcdef"},
    };

    const std::vector<bool> expected = {
        true,
        false,
        true,
        true,
        true
    };

    int i = 0;
    for (auto test : tests)
    {
        auto soln = sol.isSubsequence(test[0], test[1]);
        std::cout << "Soln: " << soln << std::endl;
        assert(soln == expected[i]);
        std::cout << "Test " << i << " passed.\n";
        i++;
    };

    return 0;
}

