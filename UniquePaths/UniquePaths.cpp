#include <iostream>
#include <vector>
#include <queue>

class Solution {
public:
    int uniquePaths(int m, int n) {
        
        std::queue<std::pair<int, int>> squares;
        squares.push({0, 0});
        for (auto i = 0; i < m; ++i)
        {
            for (auto j = 0; j < n; ++j)
            {
                
            }
        }

        return paths.size();
    }
private:
    std::vector<std::vector<int>> paths;
};

int main()
{
    Solution sol;
    std::cout << sol.uniquePaths(1, 1) << std::endl;

    return 0;
}