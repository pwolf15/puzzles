#include <iostream>

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

long long SwapBits(long long x, int i, int j)
{
    // check if i, j differ
    if (((x >> i) & 1) != ((x >> j) & 1))
    {
        // don't need to literal swap if i, j differ
        // just bit flip
        unsigned long long bit_mask = (1L << i) | (1L << j);

        x ^= bit_mask;
    }

    return x;
}

int main()
{
    long long result = ReverseBits_BruteForce(0xa);
    std::cout << "result: 0x" << std::hex << result << std::dec << std::endl;
    std::cout << "result: 0x" << std::hex << ReverseBits_BruteForce(0xdeadbeef) << std::dec << std::endl;
    
    return 0;
}