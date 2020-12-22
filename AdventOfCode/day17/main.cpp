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

std::vector<std::string> get_lines(std::string filename)
{
    std::vector<std::string> lines;
    std::ifstream infile(filename);
    if (!infile.good())
    {
        std::cout << "Could not open file." << std::endl;
        return lines;
    }

    std::string line;
    while (getline(infile, line))
    {
        lines.push_back(line);
    }

    return lines;
}

void initialize_grid(std::vector<std::vector<std::vector<char>>>& grid, const std::vector<std::string>& lines)
{
    std::vector<std::vector<char>> layer;
    for (auto line: lines)
    {
        
        std::vector<char> row;
        for (int i = 0; i < line.size(); ++i)
        {
            row.push_back(line[i]);
        }
        layer.push_back(row);
    }

    grid.push_back(layer);
}

int main()
{
    std::vector<std::string> lines = get_lines("../day17.txt");

    std::vector<std::vector<std::vector<char>>> grid;
    initialize_grid(grid, lines);

    for (auto row: grid[0])
    {
        for (auto col: row)
        {
            std::cout << col;
        }

        std::cout << std::endl;
    }
    
    std::cout << "Grid size: " << grid.size() << std::endl;
    std::cout << "Num lines: " << lines.size() << std::endl;

    return 0;
}