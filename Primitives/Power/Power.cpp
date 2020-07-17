#include <iostream>
#include <vector>
#include <math.h>

double power(double x, int y) 
{
    // O(y)

    // 2.1, 3, 9.261
    // (a^b)
    // 0
    double result = 1.0;
    while (y)
    {
        result *= x;
        y--;
        std::cout << "here: " << x << std::endl;
    }

    return result;
}

double power_log(double x, int y) 
{
    // O(y)
    
    // 2.1, 3, 9.261
    // (ab)^m = (a*2)
    // 0
    // (a * b) ^ m = a ^ m * b ^ m
    // 2.1 * 2.1 * 2.1 * 2.1 = 2.1^2 * 2
    double result = 1.0;
    long long power = y;
    
    if (y < 0)
    {
        power = -power, x = 1.0 / x;
    }

    while (power)
    {
        if (power & 1)
        {
            result *= x;
        }
        x *= x; power >>= 1;
    }

    return result;
}

class Solution {
public:
    double myPow(double x, int n) {
        // O(y)
    
        // 2.1, 3, 9.261
        // (ab)^m = (a*2)
        // 0
        // (a * b) ^ m = a ^ m * b ^ m
        // 2.1 * 2.1 * 2.1 * 2.1 = 2.1^2 * 2
        double result = 1.0;
        long long power = n;

        if (n < 0)
        {
            power = -power, x = 1.0 / x;
        }

        while (power)
        {
            if (power & 1)
            {
                result *= x;
            }
            x *= x; power >>= 1;
        }

        return result;
    }
};

int main()
{
    std::cout << "n complexity" << std::endl;
    std::cout << power(2.1, 3) << std::endl;
    std::cout << power_log(2.1, 3) << std::endl;

    return 0;
}