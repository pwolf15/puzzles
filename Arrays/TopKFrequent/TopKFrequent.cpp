#include <iostream>
#include <vector>
#include <math.h>
#include <vector>
#include <map>

using namespace std;

class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        
        std::map<int, int> freqs; // map from num to frequency

        // need to be able to find frequency with <= O(log n)

        for (int i = 0; i < nums.size(); ++i)
        {
            if (freqs.find(nums[i]) == freqs.end())
            {
                freqs.insert({nums[i], 1});
            }
            else
            {
                freqs.find(nums[i])->second++;
            }
        }

        std::multimap<int, int> freqToNum; // map freq to num
        for (auto freq: freqs)
        {
            freqToNum.insert({ freq.second, freq.first });
        }

        std::vector<int> kFrequent;
        auto it = freqToNum.end();
        for (auto it = freqToNum.rbegin(); it != freqToNum.rend(); ++it)
        {
            kFrequent.push_back(it->second);
            k--;
            if (k <= 0)
            {
                break;
            }
        }       

        return kFrequent;
    }
};

int main()
{
    Solution sol;
    std::vector<int> nums = {1,1,1,2,2,3,3,3,3};
    auto kFrequent = sol.topKFrequent(nums, 2);

    for (auto freq: kFrequent)
    {
        std::cout << "Freq: " << freq << std::endl;
    }

    return 0;
}