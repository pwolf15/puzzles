#include <iostream>
#include <vector>
#include <cmath>
#include <map>
#include <limits>

int ZeroOneRandom()
{
    return rand() % 2;
}

int UniformRandom_PW(int lower_bound, int upper_bound)
{
    int range = upper_bound - lower_bound + 1;
    int numBits = (int)ceil(log2(upper_bound));
    int largest = 1 << numBits;
    int result = 0;
    int validResult = upper_bound + 1;

    while (validResult > upper_bound)
    {
        // generate random number between 0 and 2^i, where is number of bits in upper_bound
        // if result + lower_bound <= upper bound, return it
        for (int i = 0; i < numBits; ++i)
        {
            result |= ZeroOneRandom() << i;
        }

        validResult = result + lower_bound;
        result = 0;
    }

    return validResult;
}

// time complexity O(log(b - a + 1))
int UniformRandom(int lower_bound, int upper_bound)
{
    int number_of_outcomes = upper_bound - lower_bound + 1;
    int result;
    do 
    {
        result = 0;
        for (int i = 0; (1 << i) < number_of_outcomes; ++i)
        {
            result = (result << 1) | ZeroOneRandom();
        }
    } while (result >= number_of_outcomes);

    return result + lower_bound; 
}

int main()
{
    srand (time(NULL));
    std::map<int, int> outcomes;
    for (int i = 0; i < 100; ++i)
    {
        int result = UniformRandom(1, 6);
        if (outcomes.find(result) == outcomes.end())
        {
            outcomes[result] = 1;
        }
        else
        {
            outcomes[result]++;
        }
    }

    for (auto outcome: outcomes)
    {
        std::cout << "outcomes[" << outcome.first << "]: " << outcome.second << std::endl;
    }

    outcomes.clear();
    std::cout << "PW: " << std::endl;
    for (int i = 0; i < 100; ++i)
    {
        int result = UniformRandom_PW(1, 6);
        if (outcomes.find(result) == outcomes.end())
        {
            outcomes[result] = 1;
        }
        else
        {
            outcomes[result]++;
        }
    }

    for (auto outcome: outcomes)
    {
        std::cout << "outcomes[" << outcome.first << "]: " << outcome.second << std::endl;
    }

    return 0;
}