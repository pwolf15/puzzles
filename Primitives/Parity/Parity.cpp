#include <iostream>

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

int main()
{
    std::cout << parity(0b10101010101) << std::endl;
    std::cout << parity(0xffffffff) << std::endl;
    std::cout << parity(0xeeeeeee) << std::endl;

    return 0;
}