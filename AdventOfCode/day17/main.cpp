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
#include <map>

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

void initialize_grid(std::map<int, std::vector<std::vector<char>>>& grid, const std::vector<std::string>& lines)
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

    grid[0] = layer;
}

bool is_valid(int x, int y, int w, int h)
{
    return (x >= 0 && x < w) && (y >= 0 && y < h);
}

int count_cubes(std::map<int, std::vector<std::vector<char>>>& grid, int x, int y, int z)
{
    int count = 0;
    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <=1; j++)
        {
            for (int k = -1; k <=1; k++)
            {
                if (i == 0 && j == 0 && k == 0) continue;

                if (grid.find(z + k) == grid.end())
                {
                    continue;
                }

                auto layer1 = grid.find(z + k)->second;
                if (!is_valid(j + x, i + y, layer1[0].size(), layer1.size()))
                {
                    continue;
                }

                if (layer1[i+y][j+x] == '#')
                {
                    count++;
                }
            }
        }
    }

    return count;
}

std::vector<std::vector<char>> get_new_layer(std::vector<std::vector<char>> layer)
{
    std::vector<char> top(layer[0].size() + 2, '.');
    std::vector<char> bottom(layer[0].size() + 2, '.');
    std::vector<std::vector<char>> new_layer;
    new_layer.push_back(top);
    for (int i = 0; i < layer.size(); i++)
    {
        std::vector<char> new_row;
        new_row.push_back('.');
        for (int j = 0; j < layer[0].size(); j++)
        {
            new_row.push_back(layer[i][j]);
        }
        new_row.push_back('.');
        new_layer.push_back(new_row);
    }
    new_layer.push_back(bottom);
    return new_layer;
}

void update_grid(std::map<int, std::vector<std::vector<char>>>& grid)
{
    std::vector<std::vector<char>> old_layer_resized;
    std::vector<std::vector<char>> old_layer = grid.find(0)->second;
    old_layer_resized = get_new_layer(old_layer);
    grid[0] = old_layer_resized;
}

void step(std::map<int, std::vector<std::vector<char>>>& grid)
{
    int counter = 0;

    std::vector<std::vector<char>> new_layer;
    update_grid(grid);
    std::vector<std::vector<char>> layer = grid[0];

    for (int i = 0; i < layer.size(); i++)
    {
        std::vector<char> new_layer_row;
        for (int j = 0; j < layer[0].size(); j++)
        {
            int cube_count = count_cubes(grid, j, i, 0);
            if (layer[i][j] == '#' && (cube_count == 2 || cube_count == 3))
            {
                new_layer_row.push_back('#');
            }
            else if (layer[i][j] == '.' && cube_count == 3)
            {
                new_layer_row.push_back('#');
            }
            else
            {
                new_layer_row.push_back('.');
            }
        }
        new_layer.push_back(new_layer_row);
    }

    grid[0] = new_layer;
}

void print_layer(std::vector<std::vector<char>> layer)
{
    for (auto row: layer)
    {
        for (auto col: row)
        {
            std::cout << col;
        }

        std::cout << std::endl;
    }
}

int main()
{
    std::vector<std::string> lines = get_lines("../day17.txt");

    std::map<int, std::vector<std::vector<char>>> grid;
    initialize_grid(grid, lines);

    print_layer(grid[0]);

    step(grid);

    print_layer(grid[0]);

    std::cout << "Grid size: " << grid.size() << std::endl;
    std::cout << "Num lines: " << lines.size() << std::endl;

    return 0;
}