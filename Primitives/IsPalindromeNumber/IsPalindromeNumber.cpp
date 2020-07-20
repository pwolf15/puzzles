#include <iostream>
#include <vector>
#include <math.h>

// O(n) time complexity, O(n) space complexity
bool IsPalindromeNumber_BF(int x)
{
    std::string xStr = std::to_string(x);
    if (xStr[0] == '-')
    {
        return false;
    }

    for (size_t i = 0; i < xStr.size() / 2; i++)
    {
        if (xStr[i] != xStr[xStr.size() - i - 1])
        {
            return false;
        }
    }

    return true;
}

// O(n): n digits in x
long long Reverse(int x)
{
    long long result = 0;

    while (x)
    {
        result = result * 10 + x % 10;
        x /= 10;
    }

    return result;
}

// O(n) time complexity, O(n) space complexity
bool IsPalindromeNumber_Reverse(int x)
{
    return x == Reverse(x);
}

// O(n) time complexity, O(n) space complexity
bool IsPalindromeNumber_SpaceEfficient(int x)
{
    if (x <= 0)
    {
        return x == 0;
    }

    int msd = log10(x);
    int msd_mask = pow(10, msd);
    bool match = true;
    while (x)
    {
        int largestDigit = (x / msd_mask);
        int smallestDigit = x % 10;

        #ifdef DEBUG
        std::cout << "MSD: " << msd << std::endl;
        std::cout << "MSD mask: " << msd_mask << std::endl;
        std::cout << "LD: " << largestDigit << "\n";
        std::cout << "SD: " << smallestDigit << "\n";
        #endif

        if (largestDigit != smallestDigit)
        {
            match = false;
            break;
        }

        x %= msd_mask;      // remove MSD
        x /= 10;            // remove LSD
        msd_mask /= 100;
    }

    return match;
}

int main()
{
    std::vector<int> tests = {314, 12344321, 0, 12321, 12343321};

#ifdef RUNALL
    for (auto test : tests)
    {
        std::cout << IsPalindromeNumber_BF(test) << std::endl;
    }

    for (auto test : tests)
    {
        std::cout << IsPalindromeNumber_Reverse(test) << std::endl;
    }
#endif

    for (auto test : tests)
    {
        bool palindrome = IsPalindromeNumber_SpaceEfficient(test);
        std::cout << "Palindrome: " << palindrome << std::endl;
    }

    return 0;
}