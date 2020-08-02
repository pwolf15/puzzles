#include "Strings.hpp"

#include <unordered_map>
#include <numeric>
#include <unordered_set>
#include <iostream>
#include <algorithm>

int firstUniqueChar_brute(std::string s)
{
    // 1. remove all duplicate characters
    // 2. get first index
    std::unordered_set<char> repeatedChars;
    std::unordered_set<char> uniqueChars;

    int i = 0;
    for (auto c: s)
    {
        if (repeatedChars.find(c) != repeatedChars.end())
        {
            // repeated, continue
        }
        else if (uniqueChars.find(c) == uniqueChars.end())
        {
            // not seen yet; add to unique list
            uniqueChars.insert(c);
        }
        else if (uniqueChars.find(c) != uniqueChars.end())
        {
            // seen already; remove from unique list and to repated
            uniqueChars.erase(c);
            repeatedChars.insert(c);
        }
        
        i++;
    }

    int firstIndex = -1; 
    i = 0;
    for (auto c: s)
    {
        if (uniqueChars.find(c) != uniqueChars.end())
        {
            firstIndex = i;
            break;
        }

        i++;
    }

    return firstIndex;
}

// Given a string, find the first non-repeating character in it and return its index. 
// If it doesn't exist, return -1.
int firstUniqChar(std::string s)
{
    return firstUniqueChar_brute(s);
}

bool isAnagram(std::string s, std::string t)
{
    std::sort(s.begin(), s.end());
    std::sort(t.begin(), t.end());
    return s == t;
}

bool detectCapitalUse(std::string word)
{
    size_t i = 0;
    enum UseType {
        NONE,
        ALL_CAPS,
        FIRST_CAPS,
        FIRST_CAPS_ONLY,
        NO_CAPS,
        INCORRECT
    };

    UseType usage = UseType::NONE;
    if (word.empty())
    {
        return true;
    }

    if (isupper(word[0]))
    {
        usage = UseType::FIRST_CAPS;
    }
    else
    {
        usage = UseType::NO_CAPS;
    }

    if (word.size() == 1)
    {
        return true;
    }
    
    for (auto c: word.substr(1))
    {
        // if current is not a capital,
        //  but second capital was found
        if (!isupper(c) && usage == UseType::ALL_CAPS)
        {
            usage = UseType::INCORRECT;
            break;
        }
        else if (!isupper(c) && usage == UseType::FIRST_CAPS)
        {
            usage = UseType::FIRST_CAPS_ONLY;
        }
        else if (isupper(c) && usage == UseType::NO_CAPS)
        {
            usage = UseType::INCORRECT;
            break;
        }
        else if (isupper(c) && usage == UseType::FIRST_CAPS)
        {
            usage = UseType::ALL_CAPS;
        }
        else if (isupper(c) && usage == UseType::FIRST_CAPS_ONLY)
        {
            usage = UseType::INCORRECT;
            break;
        }
    }

    return usage != UseType::INCORRECT;
}