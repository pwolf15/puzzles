#include <vector>
#include <iostream>
#include <assert.h>
#include <sstream>
#include <string>
#include <iterator>

using namespace std;

// split
std::vector<std::string> split(std::string const &input) { 
    std::istringstream buffer(input);
    std::vector<std::string> ret;

    std::copy(std::istream_iterator<std::string>(buffer), 
              std::istream_iterator<std::string>(),
              std::back_inserter(ret));
    return ret;
}

class Solution {
public:
    int lengthOfLastWord(string s) {
        return efficientLinear(s);
    }
private:
    int linearSolution(string s) {
        
        int size = 0;
        auto words = split(s);

        if (words.size())
        {
            return words[words.size() - 1].size();
        }
        else 
        {
            return 0;
        }
    }

    int efficientLinear(string s) {

        int size = 0;
        int i = s.size() - 1;
        bool foundWord = false;
        while (i >= 0)
        {
            if (!foundWord)
            {
                if (s[i] != ' ')
                {
                    foundWord = true;
                    size++;
                }

                --i;
            }
            else
            {
                // found word

                if (s[i] != ' ')
                {
                    size++;
                }
                else
                {
                    break;
                }
            }
        }

        return size;
    }
};

int main()
{

    Solution sol;

    const auto tests = {
        "Hello World",
        "Hello!",
        ""
    };

    const std::vector<int> expected = {
        5,
        6,
        0
    };

    int i = 0;
    for (auto test: tests)
    {
        auto soln = sol.lengthOfLastWord(test);
        assert(soln == expected[i]);
        std::cout << "Test " << i << " passed.\n";
        i++;
    };

    return 0;
}