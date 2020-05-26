#include <vector>
#include <iostream>
#include <assert.h>
#include <sstream>
#include <string>
#include <iterator>
#include <algorithm>

using namespace std;

class Solution {
public:
    int maxUncrossedLines(vector<int> A, vector<int> B) {
        
        size_t aIndex = 0;
        size_t bIndex = 0;
        size_t count = 0;

        if (aIndex >= A.size() || bIndex >= B.size())
        {
            return count;
        }
        else if (A[aIndex] == B[bIndex])
        {
            return 1 + 
                maxUncrossedLines(std::vector<int>(A.begin() + 1, A.end()), std::vector<int>(B.begin() + 1, B.end()));
               
        }
        else 
        {
            return std::max(
                maxUncrossedLines(std::vector<int>(A.begin(), A.end()), std::vector<int>(B.begin() + 1, B.end())),
                maxUncrossedLines(std::vector<int>(A.begin() + 1, A.end()), std::vector<int>(B.begin(), B.end())));
        }
    }
private:
    
};

int main()
{

    Solution sol;

    const std::vector<std::vector<std::vector<int>>> tests = {
        { { 1,4,2 }, { 1,2,4 }},
        { { 2,5,1,2,5 }, { 10,5,2,1,5,2 }},
        { { 1,3,7,1,7,5 }, { 1,9,2,5,1 }},
        { { 3,1,4,1,1,3,5,1,2,2},
          {4,1,5,2,1,1,1,5,3,1,1,1,2,3,1,4,3,5,5,3,1,2,3,2,4,1,1,1,5,3},
        },
    };

    const std::vector<int> expected = {
        2,
        3,
        2,
        9,
    };

    int i = 0;
    for (auto test : tests)
    {
        auto soln = sol.maxUncrossedLines(test[0], test[1]);
        std::cout << "Soln: " << soln << std::endl;
        assert(expected[i] == soln);
        std::cout << "Test " << i << " passed.\n";
        i++;
    };

    return 0;
}