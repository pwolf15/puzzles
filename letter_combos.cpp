#include <vector>
#include <map>
#include <string>
#include <iostream>

static std::map<int, std::vector<std::string>> mappings = {
    { '2', {"a", "b", "c" }},
    { '3', { "d", "e", "f"}},
    { '4', { "g", "h", "i"}},
    { '5', { "j", "k", "l"}},
    { '6', { "m", "n", "o"}},
    { '7', { "p", "q", "r", "s"}},
    { '8', { "t", "u", "v"}},
    { '9', {"w", "x", "y", "z"}}
};

static std::vector<std::string> combine(std::vector<std::string> v1, std::vector<std::string> v2)
{
    std::vector<std::string> result;
    for (auto v1Ele: v1)
    {
        for (auto v2Ele: v2)
        {
            result.push_back(v1Ele + v2Ele);
        }
    }
    
    return result;
}

class Solution {
public:
    std::vector<std::string> letterCombinations(std::string digits) {
        
        std::vector<std::string> combos;
        if (!digits.size())
        {
            return combos;
        }

        combos = mappings[digits[0]];
        for (size_t i = 1; i < digits.size(); ++i)
        {
            auto mapping = mappings[digits[i]];
            combos = combine(combos, mapping);
        }

        return combos;
    }
};

int main() 
{
    Solution sol;
    auto combos = sol.letterCombinations("23");
    std::cout << combos.size() << std::endl;
    for (auto c: combos)
    {
        std::cout << c << std::endl;
    }
}