#include <vector>
#include <iostream>
#include <assert.h>
#include <limits>
#include <algorithm>
#include <regex>

using namespace std;

class Solution {
public:
    vector<int> getRow(int rowIndex) {
        std::vector<int> row(rowIndex + 1);
        row[rowIndex / 2] = 1;
        for (int i = 0; i < rowIndex; i++)
        {
            row[rowIndex / 2 - i] = row[i];
            row[rowIndex / 2 + i] = row[i];
        }
    }
};


int main()
{

    Solution sol;

    std::cout << sol.getRow(4) << std::endl;

    return 0;
}