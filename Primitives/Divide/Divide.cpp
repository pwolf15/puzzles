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

// O(x / y) brute force => O(x)
// if y = 1, x is very large it's going to take a while
int Divide_BF(int x, int y)
{
    int result = 0;
    while (x > 0)
    {
        x -= y;
        result++;
    }

    if (x < 0)
    {
        result--;
    }

    return result;
}

// relate x / y to (x - y) / y
// 3 / 1 => (3 - 1) / 1
// 100011 (35)
// 100011 - 111 => 11100 (28) (35 - 32) => 2^5 
// 35 - 32 = 2^5
// 111 (7)
// 4 / 2 => (4 - 2) / 2
// 35 / 7 => (35 - 7) / 7, 28 / 7 = 4, 
// 35 x / y => (x - y) / y 35 => 28
// 35 / 7 => 5, 4
// 63 / 21 => 3, 42 / 21 => 2
// 11 / 4 => 2 (1011) => 11 - 8 => (2^3) + 2^1 + 2^0
// 35 / 7
// 4 / 2 = (110 / 10) => 110 => 1 11 - 10 => 1
// 100 10  >> 1 = 10
// 110 10 >> 1 11 > 
// 35 / 7 
// 100011
// 111
// 10010
// 111
// 10010 18
// 00111  7
//  1011  11
//  0111  7
//   100  4
// 10010 18
// 00111  7

int main()
{
    std::cout << Divide_BF(100, 3) << std::endl;
    return 0;
}