#include <vector>
#include <iostream>
#include <assert.h>
#include <limits>
#include <algorithm>
#include <regex>
#include <unordered_map>

using namespace std;

class Solution {
public:
    int numSquares(int n) {
        
        auto it = squares.find(n);

        if (it != squares.end())
        {
            // if already stored as square, return value in map
            return it->second;
        }
        else if (n <= 1)
        {
            return n;
        }
        else
        {
            int num = n;
            for (int i = 1; i * i <= n; ++i)
            {
                // get min of current least numSquares or current difference of n and square of i + 1
                num = min(num, numSquares(n - i * i) + 1);
            }
            squares[n] = num;
            return num;
        }
    }
private:
    std::unordered_map<int, int> squares;
};

int main()
{

    Solution sol;

    std::cout << sol.numSquares(12) << std::endl;
    std::cout << sol.numSquares(4) << std::endl;
    std::cout << sol.numSquares(225) << std::endl;
    std::cout << sol.numSquares(225) << std::endl;

    return 0;
}