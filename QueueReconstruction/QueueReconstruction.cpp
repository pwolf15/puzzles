#include <vector>
#include <iostream>
#include <assert.h>
#include <limits>
#include <algorithm>
#include <map>
#include <set>
#include <list>

using namespace std;

void print(vector<vector<int>> v)
{
    for (auto i: v)
    {
        std::cout << "[" << i[0] << "," << i[1] << "]" << std::endl;
    }
}
class Solution {
public:
    vector<vector<int>> reconstructQueue(vector<vector<int>>& people) {
        
        if (people.empty())
        {
            return people;
        }

        vector<vector<int>> reconstructed;
        auto cmp = [](vector<int> a, vector<int> b) {
            return a[0] < b[0];
        };
        std::sort(people.begin(), people.end(), cmp);
        reconstructed.resize(people.size(), {-1, 0});
        std::vector<int> positions;
        for (int i = 0; i < people.size(); i++)
        {
            positions.push_back(i);
        }

        std::vector<int> toErase;
        int curHeight = people[0][0];
        for (int i = 0; i < people.size(); ++i)
        {
            auto offset = people[i][1];
            auto height = people[i][0];

            if (height > curHeight)
            {
                curHeight = height;
                std::sort(toErase.begin(), toErase.end());
                for (int j = toErase.size() - 1; j >= 0; j--)
                {
                    positions.erase(positions.begin() + toErase[j]);
                }
                toErase.clear();
            }
            auto iter = positions.begin() + offset;
            reconstructed[*iter] = people[i];
            toErase.push_back(offset);
            
        }

        return reconstructed;
    }
};

int main()
{
    // vector<vector<int>> v = {{7,0}, {4,4}, {7,1}, {5,0}, {6,1}, {5,2}};
    vector<vector<int>> v = {{9,0},{7,0},{1,9},{3,0},{2,7},{5,3},{6,0},{3,4},{6,2},{5,2}};
    Solution sol;
    vector<vector<int>> reconstructed = sol.reconstructQueue(v);
                        print(reconstructed);
    // print(reconstructed);

    return 0;
}