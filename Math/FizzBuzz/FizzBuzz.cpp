#include <vector>
#include <string>
#include <iostream>

using namespace std;

class Solution
{
public:
    vector<string> fizzBuzz(int n)
    {

        std::vector<string> result;
        for (size_t i = 1; i <= n; i++)
        {
            if (i % 3 == 0 && i % 5 == 0)
            {
                result.push_back("FizzBuzz");
            }
            else if (i % 3 == 0)
            {
                result.push_back("Fizz");
            }
            else if (i % 5 == 0)
            {
                result.push_back("Buzz");
            }
            else
            {
                result.push_back(std::to_string(i));
            }
        }

        return result;
    }
};

int main()
{
    Solution sol;
    auto results = sol.fizzBuzz(15);
    for (auto result : results)
    {
        std::cout << result << std::endl;
    }
    return 0;
}