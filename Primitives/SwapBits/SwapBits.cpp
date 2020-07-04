#include <iostream>

long long SwapBits_BruteForce(long long x, int i, int j) 
{
    bool iBit = (x >> i) & 0x1;
    bool jBit = (x >> j) & 0x1;

    // unset existing bit
    x = ((iBit << j) | (x & ~(1 << j)));
    x = ((jBit << i) | (x & ~(1 << i)));

    return x;
}

long long SwapBits(long long x, int i , int j)
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
    std::cout << std::hex << SwapBits(0xf, 1, 8) << std::dec << std::endl;
    return 0;
}