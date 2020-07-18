#include <iostream>
#include <vector>
#include <cmath>
#include <limits>

long long Reverse_BF(int x)
{
    std::string xStr = std::to_string(x);
    std::string reversed = "";

    int idx = 0;
    if (xStr[0] == '-')
    {
        reversed +=  '-';
        idx++;
    }

    for (int i = xStr.size() - 1; i >= idx; --i)
    {
        reversed += xStr[i];
    }

    return std::stoull(reversed);
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


int main()
{
    long long result = Reverse_BF(314);
    std::cout << result << std::endl;
    result = Reverse_BF(-314);
    std::cout << result << std::endl;
    result = Reverse(314);
    std::cout << result << std::endl;
    result = Reverse(-314);
    std::cout << result << std::endl;

    return 0;
}