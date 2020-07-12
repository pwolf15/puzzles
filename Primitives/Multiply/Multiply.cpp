#include <iostream>
#include <vector>
#include <math.h>

unsigned long long Multiply_add(unsigned long long x, unsigned long long y)
{
    int result = 0;
    while (y)
    {
        result += x;
        y--;
    }

    return result;
}

unsigned long long add_bw(unsigned long long x, unsigned long long y);

unsigned long long Multiply_bw(unsigned long long x, unsigned long long y)
{
    int result = 0;

    while (y)
    {  
        if (y & 1)
        {
            result = add_bw(result, x);
        }
        
        y >>= 1;
        x <<= 1;
    }

    return result;
}

unsigned long long add_bw(unsigned long long x, unsigned long long y)
{
    while (y)
    {
        unsigned long long carry = x & y;   // sum
        x = x ^ y;                          // carry
        y = carry << 1;
    }

    return x;
}

int main()
{
    // std::cout << Multiply_bit(7, 5) << std::endl;
    std::cout << 0b100011 << std::endl;
    std::cout << add_bw(1, 1) << std::endl;
    std::cout << add_bw(10000, 10000) << std::endl;
    std::cout << Multiply_bw(3, 3) << std::endl;
    std::cout << Multiply_bw(10000, 10000) << std::endl;

    return 0;
}