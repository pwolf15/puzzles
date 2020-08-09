#include "Primitives.hpp"

#include <math.h>
#include <iostream>
#include <numeric>
#include <algorithm>

// Known as Digital Root
// below is basic logarithmic solution
// Given a non-negative integer num,
// repeatedly add all its digits until the result has only one digit.
// time complexity: O(log10(n))
int addDigits_log(int num)
{
    int result = 0;
    while (num)
    {
        // sum digits of num and move into result
        // if result greater than or equal to 10, start again
        result += num % 10;
        num /= 10;

        if (num == 0 && result >= 10)
        {
            num = result;
            result = 0;
        }
    }

    return result;
}

int addDigits_constant(int num)
{
    return num == 0 ? 0 : 1 + (num - 1) % 9;
}

int addDigits(int num)
{
    return addDigits_constant(num);
}

// Write a function that takes an unsigned integer and return the number of '1' bits it has
// (also known as the Hamming weight).
// redundant with EPI Count Bits
int hammingWeight(uint32_t n)
{
    int numBits = 0;
    while (n)
    {
        numBits += n & 1;
        n >>= 1;
    }

    return numBits;
}

bool isPowerOfThree(int n)
{
    long long powered = 0;
    bool powerOfThree = false;
    size_t i = 0;
    while (powered < n)
    {
        powered = pow(3, i);
        i++;

        if (powered == n)
        {
            powerOfThree = true;
            break;
        }
    }

    return powerOfThree;
}

int missingNumber(std::vector<int> &nums)
{

    int expectedSum = (nums.size() + 1) * (nums.size()) / 2;
    int actualSum = std::accumulate(nums.begin(), nums.end(), 0);
    return expectedSum - actualSum;
}

int countPrimes_BF(int n)
{
    auto isPrime = [](int n) {
        for (int i = 1; i < n; ++i)
        {
            if (n % i == 0 && i != 1)
            {
                return false;
            }
        }

        return true;
    };

    std::vector<int> primes;
    for (int i = 2; i < n; ++i)
    {
        if (isPrime(i))
        {
            primes.push_back(i);
        }
    }

    return primes.size();
}

int sieve(int n)
{
    std::vector<int> nums(n, 1);

    if (n < 2)
    {
        return 0;
    }
    
    for (int i = 2; i < n; ++i)
    {
        if (nums[i])
        {
            for (int j = i * 2; j < n; j += i)
            {
                nums[j] = 0;
            }
        }
    }

    int i = 0;
    nums[0] = 0;
    nums[1] = 0;

    auto result = std::count_if(nums.begin(), nums.end(), [](int n) {
        return n;
    });

    return result;
}

int countPrimes(int n)
{
    return sieve(n);
}

bool isPowerOfFour(int n)
{
    long long powered = 0;
    bool powerOfFour = false;
    size_t i = 0;
    while (powered < n)
    {
        powered = pow(4, i);
        i++;

        if (powered == n)
        {
            powerOfFour = true;
            break;
        }
    }

    return powerOfFour;
}