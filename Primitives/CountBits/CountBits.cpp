#include <iostream>

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

int main()
{
    std::cout << CountBits(15) << std::endl;
    std::cout << CountBits(0xAAAAAAAA) << std::endl;
    return 0;
}