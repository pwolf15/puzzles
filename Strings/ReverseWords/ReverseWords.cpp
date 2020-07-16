#include <vector>
#include <iostream>
#include <assert.h>
#include <limits>
#include <algorithm>

using namespace std;

class Solution {
public:
    string reverseWords(string s) {
        
        std::vector<std::string> words;
        while (!s.empty())
        {
            size_t startWord = s.find_first_not_of(" ");
            if (startWord == std::string::npos)
            {
                break;
            }

            s = s.substr(startWord);
            size_t endWord = std::min(s.find_first_of(" "), s.size());
            words.push_back(s.substr(0, endWord));
            s = s.substr(endWord);
        }

        std::string reversed = "";
        for (auto word: words)
        {
            if (!reversed.empty())
            {
                reversed = " " + reversed;
            }

            reversed = word + reversed;
        }

        return reversed;
    }
};

int main()
{

    Solution sol;

    std::cout << sol.reverseWords("  hello world!  ") << std::endl;
    return 0;
}