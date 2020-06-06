#include <vector>
#include <iostream>
#include <assert.h>
#include <limits>
#include <algorithm>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

using namespace std;

class Solution {
public:
    Solution(vector<int>& w) {
        
        srand (time(NULL));

        for (auto weight: w)
        {
            if (probs.empty())
            {
                probs.push_back(weight);
            }
            else
            {
                probs.push_back(probs.back() + weight);
            }
        }
    }
    
    int pickIndex() {
        int total = probs.back();
        int i = rand() % total;
        auto it = upper_bound(probs.begin(), probs.end(), i);
        return it - probs.begin();
    }

private:
    vector<int> probs; 
};

int main()
{
    std::vector<int> test({1, 10});
    Solution sol(test);
    srand (time(NULL));
    
    for (int i = 0; i < 10; i++)
    {
        std::cout << sol.pickIndex() << std::endl;
    }

    return 0;
}