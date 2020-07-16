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

int Divide(int x, int y)
{
    // how many times does k * 2^n (think like long division)
    int quotient = 0;
    while (x >= y)
    {
        int logX = log2(x);
        int logY = log2(y);
        int operand = y << (logX - logY);
        int shiftAmt = (logX - logY);
        if (operand > x)
        {
            operand >>= 1;
            shiftAmt -= 1;
        }

        #ifdef DEBUG
        std::cout << "x: " << x << std::endl;
        std::cout << "log2x: " << logX << std::endl;
        std::cout << "log2y: " << logY << std::endl;
        std::cout << "quotient: " << quotient << std::endl;
        std::cout << "dividend: " << operand << std::endl;
        #endif

        x -= operand;
        quotient += 1 << shiftAmt;
    }

    return quotient;
}

int Divide_alt(int x, int y)
{
    // how many times does k * 2^n (think like long division)
    int quotient = 0;
    int power = 32;
    unsigned long long y_power = static_cast<unsigned long long>(y) << power;
    while (x >= y)
    {
        while (y_power > x)
        {
            y_power >>= 1;
            --power;
        }

        #ifdef DEBUG
        std::cout << "x: " << x << std::endl;
        std::cout << "power: " << power << std::endl;
        std::cout << "y_power: " << y_power << std::endl;
        std::cout << "quotient: " << quotient << std::endl;
        #endif

        x -= y_power;
        quotient += 1 << power;
    }

    return quotient;
}

int main()
{
    std::cout << Divide(7, 4) << std::endl;
    std::cout << Divide(225, 15) << std::endl;
    std::cout << Divide(100, 3) << std::endl;
    std::cout << Divide(1e6, 1) << std::endl;
    std::cout << Divide(189234, 23) << std::endl;
    std::cout << Divide_alt(189234, 23) << std::endl; 

    return 0;
}