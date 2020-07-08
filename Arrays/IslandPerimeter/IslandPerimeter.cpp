#include <iostream>
#include <vector>
#include <math.h>

class Solution
{
public:
    int islandPerimeter(std::vector<std::vector<int>> &grid)
    {
        int perimeter = 0;
        for (int i = 0; i < grid.size(); ++i)
        {
            for (int j = 0; j < grid[i].size(); j++)
            {
                if (grid[i][j] == 1)
                {
                    std::vector<std::vector<int>> squares = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
                    for (auto square: squares)
                    {
                        if (!isValidSquare(i + square[0], j + square[1], grid.size(), grid[0].size()))
                        {
                            perimeter++;
                        }
                        else if (grid[i + square[0]][j + square[1]] == 0)
                        {
                            perimeter++;
                        }
                    }
                }
            }
        }

        return perimeter;
    }
    
    bool isValidSquare(int i, int j, int height, int width)
    {
        return (i >= 0 && i < height) && (j >= 0 && j < width);
    }
};

int main()
{
    Solution sol;
    std::vector<std::vector<int>> inCells =
        {{0, 1, 0, 0},
         {1, 1, 1, 0},
         {0, 1, 0, 0},
         {1, 1, 0, 0}};

    std::cout << sol.islandPerimeter(inCells) << std::endl;
    inCells = {{1, 1}};
    std::cout << sol.islandPerimeter(inCells) << std::endl;

    return 0;
}