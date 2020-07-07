#include <iostream>
#include <cmath>

short CountBits(unsigned int x) 
{
    int numBits = 0;
    while (x)
    {
        numBits += x & 1;
        x >>= 1;
    }

    return numBits;
}

unsigned long long ClosestIntegerSameWeight_BruteForce(unsigned long long x)
{
    unsigned long long dist = 1;
    short numBitsX = CountBits(x);
    std::cout << "num bits: " << numBitsX << std::endl;
    // O(n * n)
    // very costly for powers of 2 (2^8, closest is 2^7, needs to check 2^7 * 2)
    while (true)
    {
        if (CountBits(x + dist) == numBitsX)
        {
            return x + dist;
        }
        else if (CountBits(x - dist) == numBitsX)
        {
            return x - dist;
        }

        dist++;
    }
}

unsigned long long ClosestIntegerSameWeight(unsigned long long x)
{
    short numBits = sizeof(unsigned long long) * 8;
    for (int i = 0; i < numBits - 1; ++i)
    {
        unsigned long long swapped = 0;

        // if swapped result not equal to x, return swapped
        if (((x >> i) & 1UL) != ((x >> (i + 1)) & 1UL)) 
        {
            // don't need to literal swap if i, j differ
            // just bit flip
            unsigned long long bit_mask = (1UL << (i)) | (1UL << (i + 1));
            x ^= bit_mask;
            return x;
        }
    }

    throw std::invalid_argument("Must not provide 0 or 0xffff'ffff'ffff'ffff");
}

int main()
{
    std::cout << std::hex << ClosestIntegerSameWeight(14) << std::hex << std::endl;
    std::cout << std::hex << ClosestIntegerSameWeight(6) << std::hex << std::endl;
    std::cout << std::hex << ClosestIntegerSameWeight(pow(2, 31)) << std::hex << std::endl;
    std::cout << std::hex << ClosestIntegerSameWeight(0) << std::hex << std::endl;
    std::cout << std::dec << ClosestIntegerSameWeight(0xffffffffffffffff) << std::hex << std::endl;
    return 0;
}