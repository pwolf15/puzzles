#include <iostream>
#include <vector>
#include <math.h>

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

int main()
{
    std::cout << IsPalindromeNumber_BF(314) << std::endl;
    std::cout << IsPalindromeNumber_BF(12344321) << std::endl;
    std::cout << IsPalindromeNumber_BF(0) << std::endl;
    std::cout << IsPalindromeNumber_BF(12321) << std::endl;


    return 0;
}