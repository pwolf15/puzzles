#include <vector>
#include <iostream>
#include <assert.h>
#include <limits>
#include <algorithm>

using namespace std;

#include <iostream>

int sumOfMultiples3And5(int n)
{
    int sum = 0;
    for (int i = 0; i < n; i++)
    {
        if ((i % 3 == 0) || (i % 5 == 0))
        {
            sum += i;
        }
    }

    return sum;
}

unsigned long long sumOfEvenFib()
{
    int limit = 4000000;
    int n = 2;
    unsigned long long sum = 0;
    unsigned long long a = 1;
    unsigned long long b = 2;
    unsigned long long c = 0;

    // initial value;
    sum += 2;

    while (c < limit)
    {
        c = a + b;
        if (c % 2 == 0)
            sum += c;

        a = b;
        b = c;
        n++;
    }

    return sum;
}

unsigned long long primeFactor(unsigned long long n)
{
    int prod = 1;
    int i = 2;
    for (; i < n; i++)
    {
        if (n % i == 0)
        {
            std::cout << "i: " << i << std::endl;
            n = n / (prod * i);
            // std::cout << "n: " << n << std::endl;
            i = 2;
        }
    }

    return i;
}
int main()
{
    #define PRIME_FACTOR
    #ifdef SUM_OF_MULTIPLES_35
    std::cout << sumOfMultiples3And5(10) << std::endl;
    std::cout << sumOfMultiples3And5(1000) << std::endl;
    #endif

    #ifdef EVEN_FIB
    std::cout << sumOfEvenFib() << std::endl;
    #endif

    #ifdef PRIME_FACTOR
    std::cout << primeFactor(13195) << std::endl;
    std::cout << primeFactor(600851475143) << std::endl;
    #endif

    return 0;
}