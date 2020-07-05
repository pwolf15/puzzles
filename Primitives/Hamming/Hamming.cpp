#include <iostream>
#include <vector>
#include <math.h>

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

int32_t hamming(unsigned long long x, unsigned long long y)
{
    int diff = x ^ y;
    std::cout << "diff: " << std::hex << diff << std::dec << std::endl;
    return CountBits(diff);
}

class Solution
{
public:
    int hammingDistance(int x, int y)
    {
        return CountBits(x ^ y);
    }

private:
    short CountBits(unsigned int x)
    {
        int numBits = 0;
        while (x)
        {
            x &= (x - 1);
            numBits++;
        }

        return numBits;
    }
};

int main()
{
    std::cout << hamming(0xfffffff, 0xffffffff) << std::endl;
    Solution sol;
    std::cout << sol.hammingDistance(0xfffffff, 0xffffffff) << std::endl;
    std::cout << sol.hammingDistance(0x4, 0x1) << std::endl;

    return 0;
}