#include <iostream>
#include <vector>
#include <cmath>
#include <limits>

unsigned long long ReverseBits_BruteForce(unsigned long long x)
{
    size_t numBits = sizeof(unsigned long long) * 8;

    for (int i = 0; i < numBits / 2; ++i)
    {
        long long hBit = (x >> (numBits - i - 1)) & 0x1;
        long long lBit = (x >> i) & 0x1;

        // unset existing bits
        x &= ~(1LL << (numBits - i - 1));
        x &= ~(1LL << i);
        x |= (lBit << (numBits - i - 1));
        x |= (hBit << i);
    }

    return x;
}

std::vector<unsigned long long> reversed;
bool initCache = false;

unsigned long long ReverseBits_Cached(unsigned long long x)
{
    if (!initCache)
    {
        size_t shortMax = std::numeric_limits<unsigned short>::max();
        reversed.resize(shortMax + 1);
        for (size_t num = 0; num < reversed.size(); num++)
        {
            int numBits = sizeof(unsigned short) * 8;
            unsigned short result = num;
            for (int i = 0; i < numBits / 2; ++i)
            {
                long long hBit = (result >> (numBits - i - 1)) & 0x1;
                long long lBit = (result >> i) & 0x1;

                // unset existing bits
                result &= ~((short)1L << (numBits - i - 1));
                result &= ~((short)1L << i);
                result |= (lBit << (numBits - i - 1));
                result |= (hBit << i);
            }

            reversed[num] = result;
        }

        initCache = true;
    }

    size_t mask = 0xffff;
    size_t maskSize = 16;

    // complexity is O(n / L) where n is n-bit integer and L is number of bits in cached keys
    return  ((long long)reversed[(x >> maskSize * 3) & mask]) | 
            (((long long)reversed[(x >> maskSize * 2) & mask]) << maskSize) |
            (((long long)reversed[(x >> maskSize) & mask]) << maskSize * 2) |
            (((long long)reversed[x & mask]) << maskSize * 3);
}

int main()
{
    long long result = ReverseBits_BruteForce(0xa);
    // std::cout << "result: 0x" << std::hex << result << std::dec << std::endl;
    // std::cout << "result: 0x" << std::hex << ReverseBits_BruteForce(0xdeadbeef) << std::dec << std::endl;
    std::cout << "result: 0x" << std::hex << ReverseBits_Cached(0xffffffff) << std::endl;

    return 0;
}