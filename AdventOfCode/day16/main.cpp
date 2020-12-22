#include <algorithm>
#include <fstream>
#include <math.h>
#include <numeric>
#include <unordered_set>
#include <stack>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <bitset>

void get_seq(std::vector<int>& start_seq, int limit)
{
    int counter = start_seq.size() + 1;
    std::unordered_map<int, std::vector<int>> found_nums;
    
    // initialize
    for (int i = 0; i < start_seq.size(); ++i)
    {
        std::vector<int> appearances;
        appearances.push_back(i + 1);
        found_nums[start_seq[i]] = appearances;
    }

    while (counter <= limit)
    {
        int prev_num = start_seq[start_seq.size() - 1];
        std::vector<int>& appearances = found_nums.find(prev_num)->second;
        if (appearances.size() == 1)
        {
            start_seq.push_back(0);
            found_nums[0].push_back(counter);
        }
        else
        {
            int diff = appearances[appearances.size() - 1] - appearances[appearances.size() - 2];
            start_seq.push_back(diff);
            if (found_nums.find(diff) == found_nums.end())
            {
                std::vector<int> new_appearances;
                new_appearances.push_back(counter);
                found_nums[diff] = new_appearances;
            }
            else
            {
                std::vector<int>& appearances = found_nums.find(diff)->second;
                appearances.push_back(counter);
            }
        }

        counter++;
    }
}

int main()
{
    std::vector<int> start_seq = { 14,1,17,0,3,20 };
    get_seq(start_seq, 2020);

    int turn = 0;
    for (auto num: start_seq)
    {
        std::cout << "Turn " << turn + 1 << ": " << num << std::endl;
        turn++;
    }

    std::cout << "Seq size: " << start_seq.size() << std::endl;

    return 0;
}