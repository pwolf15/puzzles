#include <vector>
#include <iostream>
#include <assert.h>
#include <sstream>
#include <string>
#include <iterator>
#include <algorithm>
#include <set>

using namespace std;

class Solution {
public:
    string getPermutation(int n, int k) {
        
        // take 1 digit add it to permutations of remaining set
        m_k = k;
        std::set<int> nums;
        for (int i = 1; i <= n; i++) 
        {
            nums.insert(i);
        }

        auto vs = generatePerms(nums);
        // for (auto s: vs)
        // {
        //     std::cout << s << std::endl;
        // }

        return vs[vs.size() - 1];
    }

private:

    int m_k;
    std::vector<std::string> generatePerms(std::set<int> nums)
    {
        auto i = 0;

        if (nums.size() == 1)
        {
            std::vector<std::string> ns;
            ns.push_back(std::to_string(*(nums.begin())));
            return ns;
        }

        std::vector<std::string> current;

        for (auto n: nums)
        {
            std::set<int> nums2 = nums;
            nums2.erase(n);
            std::vector<std::string> results = generatePerms(nums2);
            if (results.size() + current.size() > m_k)
            {
                current.push_back(std::to_string(n) + results[m_k - current.size()]);
            }
            else
            {
                current.insert(current.end(), results.begin(), results.end());
            }
            
        }

        return current;
    }
};

int main()
{

    Solution sol;

    std::string result = sol.getPermutation(9, 171669);
    std::cout << "result: " << result  << std::endl;

    return 0;
}