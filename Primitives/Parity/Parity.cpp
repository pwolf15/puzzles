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
    std::cout << std::hex << (0xc & ~(0xc - 1)) << std::hex << std::endl; // isolate lowest set bit

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

    return 0;
}