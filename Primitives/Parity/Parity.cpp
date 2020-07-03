#include <iostream>
#include <vector>
#include <math.h>

short parity(unsigned long long x) 
{
    short parity = 0;
    while (x)
    {
        parity ^= (x & 0x1);
        x >>= 1;
    }

    return parity;
}

short parity_k(unsigned long long x)
{
    short parity = 0;
    while (x)
    {
        parity ^= 1;
        x &= (x - 1);   // erase lowest set bit
    }

    return parity;
}

std::vector<int> kPreComputedParity = {};

short parity_lookup(unsigned long long x)
{
    const int kMaskSize = 16;
    const int kBitMask  = 0xFFFF;

    return  kPreComputedParity[x >> (3 * kMaskSize)] ^
            kPreComputedParity[x >> (2 * kMaskSize) & kBitMask] ^
            kPreComputedParity[x >> (1 * kMaskSize) & kBitMask] ^
            kPreComputedParity[x & kBitMask];
}

short parity_divide(unsigned long long x)
{
    x ^= x >> 32;
    x ^= x >> 16;
    x ^= x >> 8;
    x ^= x >> 4;
    x ^= x >> 2;
    x ^= x >> 1;
    return x & 0x1;
}

bool powerOfTwo(unsigned long long x)
{
    // check that isolated rightmost bit is equal to x
    // return (x & ~(x - 1)) == x;
    return !(x & (x - 1));
}

unsigned long rightPropagate(unsigned long long x)
{
    // 0b100, 0b11
    return x | (x - 1);
}

unsigned long long modPowerOfTwo(unsigned long long x, unsigned long long y)
{
    if (!powerOfTwo(y))
    {
        return 0;
    }

    int leftmost = y & ~(y - 1);
    int mask = rightPropagate(leftmost) >> 1;
    return (x ^ y) & mask;
}

int main()
{
    std::cout << "n complexity" << std::endl;
    std::cout << parity(0b10101010101) << std::endl;
    std::cout << parity(0xffffffff) << std::endl;
    std::cout << parity(0xeeeeeee) << std::endl;

    std::cout << "k = number of set bits complexity" << std::endl;
    std::cout << parity_k(0b10101010101) << std::endl;
    std::cout << parity_k(0xffffffff) << std::endl;
    std::cout << parity_k(0xeeeeeee) << std::endl;

    std::cout << "Erase lowest bit" << std::endl;
    std::cout << std::hex << (0xc & ~(0xc - 1)) << std::dec << std::endl; // isolate lowest set bit

    kPreComputedParity.resize(pow(2, 16));
    for (int i = 0; i < pow(2, 16); i++)
    {
        kPreComputedParity[i] = parity_k(i);
    }

    std::cout << "lookup complexity: O(n = word size / L = cache word size)" << std::endl;
    std::cout << parity_lookup(0b10101010101) << std::endl;
    std::cout << parity_lookup(0xffffffff) << std::endl;
    std::cout << parity_lookup(0xeeeeeee) << std::endl;

    std::cout << "divide complexity: O(log n)" << std::endl;
    std::cout << parity_divide(0b10101010101) << std::endl;
    std::cout << parity_divide(0xffffffff) << std::endl;
    std::cout << parity_divide(0xeeeeeee) << std::endl;

    // brute force fast on sparse inputs
    // random inputs => refinement on brute force 20% faster
    // table-based approach four times faster
    // associativity reduces run time by another factor of two
    std::cout << "power of two" << std::endl;
    for (int i = 0; i <= 16; i++)
    {
        std::cout << i << " : " << powerOfTwo(i) << std::endl;
    }

    std::cout << "mod power of two" << std::endl;
    std::cout << modPowerOfTwo(77, 2) << std::endl;
    std::cout << modPowerOfTwo(77, 64) << std::endl;
    std::cout << modPowerOfTwo(77, 128) << std::endl;
    std::cout << modPowerOfTwo(77, 16) << std::endl;
    // for (int i = 0; i <= 16; i++)
    // {
    //     std::cout << i << " : " << powerOfTwo(i) << std::endl;
    // }

    std::cout << "right propagate: " << std::endl;
    std::cout << rightPropagate(64) << std::endl;


    return 0;
}