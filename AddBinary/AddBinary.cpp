#include <vector>
#include <iostream>
#include <assert.h>
#include <string>
#include <algorithm>

using namespace std;

class Solution
{
public:
    string addBinary(string a, string b)
    {

        std::string result;
        int carryIn = 0;
        int carryOut = 0;
        size_t i = 0;

        // zero-pad
        if (a.size() < b.size())
        {
            std::string zeros = std::string(b.size() - a.size(), '0');
            a = zeros + a;
        }
        else if (b.size() < a.size())
        {
            std::string zeros = std::string(a.size() - b.size(), '0');
            b = zeros + b;
        }

        while (true)
        {
            if (i >= a.size())
            {
                if (carryIn)
                {
                    result += std::to_string(carryIn)[0];
                }

                break;
            }

            const auto pos = a.size() - 1 - i;
            
            // convert values to int
            int aVal = static_cast<int>(a[pos] - '0');
            int bVal = static_cast<int>(b[pos] - '0');
            
            // perform full add
            int sum = carryIn ^ (aVal ^ bVal);
            carryOut = (aVal & bVal) | (aVal & carryIn) | (bVal & carryIn);
            result += std::to_string(sum)[0];
            i++;
            carryIn = carryOut;
        }

        // digits currently ordered lsb -> msb
        std::reverse(result.begin(), result.end());
        return result;
    }
};

int main()
{

    Solution sol;

    const std::vector<std::vector<std::string>> tests = {
        {"0", "1"},
        {"11", "1"},
        {"1010", "1011"}};

    const std::vector<std::string> expected = {
        "1",
        "100",
        "10101"};

    int i = 0;
    for (auto test : tests)
    {
        auto soln = sol.addBinary(test[0], test[1]);
        assert(soln == expected[i]);
        std::cout << "Test " << i << " passed.\n";
        i++;
    };

    return 0;
}