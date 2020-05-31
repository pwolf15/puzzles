#include <vector>
#include <iostream>
#include <assert.h>
#include <limits>
#include <map>
#include <cctype>

using namespace std;

class Solution {
public:
    bool isPalindrome(string s) {
        
        bool isPalindrome = true;
        int i = 0;
        int j = s.size() - 1;

        if (s.empty())
        {
            return true;
        }

        while (true)
        {
            if ((i > s.size() / 2) || (j < s.size() / 2))
            {
                break;
            }

            auto c1 = std::tolower(s[i]);
            auto c2 = std::tolower(s[j]);
            if (!isalnum(c1))
            {
                i++;
                continue;
            }
            if (!isalnum(c2))
            {
                j--;
                continue;
            }
            if (c1 != c2)
            {
                i++;
                j--;
                isPalindrome = false;
                break;
            }
            else
            {
                i++;
                j--;
            }
            
        }

        return isPalindrome;
    }
};

int main()
{
    Solution sol;

    const std::vector<std::string> tests = {
        "",
        "A man, a plan, a canal: Panama",
        "race a car",
    };

    const std::vector<bool> expected = {
        true,
        true,
        false,
    };

    int i = 0;
    for (auto test : tests)
    {
        auto soln = sol.isPalindrome(test);
        std::cout << "Soln: " << soln << std::endl;
        assert(soln == expected[i]);
        std::cout << "Test " << i << " passed.\n";
        i++;
    };

    return 0;
}

