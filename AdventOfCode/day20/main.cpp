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
#include <regex>

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

struct Edges
{
    int16_t top;
    int16_t right;
    int16_t bottom;
    int16_t left;
};

struct Tile
{
    int id;
    int x;
    int y;
    Edges edges;
};

void get_edges(std::vector<std::string> tile_contents, Tile& tile)
{
    int top = 0;
    for (int i = 0; i < tile_contents[0].size(); ++i)
    {
        int val = tile_contents[0][i] == '#' ? 1 : 0;
        top |= (val << (tile_contents[0].size() - i - 1));
    }

    tile.edges.top = top;

    int bottom = 0;
    for (int i = 0; i < tile_contents[tile_contents.size() - 1].size(); ++i)
    {
        int val = tile_contents[tile_contents.size() - 1][i] == '#' ? 1 : 0;
        bottom |= (val << (tile_contents[tile_contents.size() - 1].size() - i - 1));
    }

    tile.edges.bottom = bottom;

    int right = 0;
    for (int i = 0; i < tile_contents.size(); ++i)
    {
        int val = tile_contents[i][tile_contents.size() - 1] == '#' ? 1 : 0;
        right |= (val << (tile_contents.size() - i - 1));
    }

    tile.edges.right = right;

    int left = 0;
    for (int i = 0; i < tile_contents.size(); ++i)
    {
        int val = tile_contents[i][0] == '#' ? 1 : 0;
        left |= (val << (tile_contents.size() - i - 1));
    }

    tile.edges.left = left;
}

void print_tile(const Tile& tile)
{
    std::cout << "Tile ID: " << tile.id << std::endl;
    std::cout << "Pos (x, y): " << tile.x << ", " << tile.y << std::endl;
    std::cout << "Top: " << std::bitset<10>(tile.edges.top) << std::endl;
    std::cout << "Right: " << std::bitset<10>(tile.edges.right) << std::endl;
    std::cout << "Bottom: " << std::bitset<10>(tile.edges.bottom) << std::endl;
    std::cout << "Left: " << std::bitset<10>(tile.edges.left) << std::endl << std::endl;
}

void get_tiles(const std::vector<std::string>& lines, std::vector<Tile>& tiles)
{
    std::vector<std::string> tile_contents;
    Tile tile;

    for (int i = 0; i < lines.size(); ++i)
    {
        auto line = lines[i];
        if (line.find("Tile") != std::string::npos)
        {
            std::string tileId = line.substr(line.find("Tile") + 5, line.find(":") - (line.find("Tile") + 5));
            tile.id = std::stoi(tileId);
        }
        else if (line == "")
        {
            get_edges(tile_contents, tile);
            tile.x = 0;
            tile.y = 0;
            tiles.push_back(tile);
            tile_contents.clear();
            print_tile(tile);
        }
        else
        {
            tile_contents.push_back(line);
        }
    }

    get_edges(tile_contents, tile);
    tile.x = 0;
    tile.y = 0;
    tiles.push_back(tile);
    tile_contents.clear();
    print_tile(tile);
}

Tile flip(Tile tile)
{
    Tile flipped = tile;
    std::swap(flipped.edges.top, flipped.edges.bottom);

    int new_left = 0;
    for (int i = 0; i < 10; i++)
    {
        new_left |= ((flipped.edges.left >> i) & 0x1) << (10 - i - 1);
    }

    flipped.edges.left = new_left;

    int new_right = 0;
    for (int i = 0; i < 10; i++)
    {
        new_right |= ((flipped.edges.right >> i) & 0x1) << (10 - i - 1);
    }

    flipped.edges.right = new_right;

    return flipped;
}

void reorder(std::vector<Tile> tiles)
{
    std::vector<std::vector<int>> image;
    for (int i = 0; i < 3; i++)
    {
        std::vector<int> image_row;
        for (int j = 0; j < 3; j++)
        {
            image_row.push_back(-1);
        }
        image.push_back(image_row);
    }
    
    while (true)
    {
        for (auto tile: tiles)
        {
            std::unordered_map<int, Tile> remaining_tiles;
            for (auto t: tiles)
            {
                remaining_tiles[t.id] = t;
            }
            
            remaining_tiles.erase(tile.id);
            image[0][0] = tile.id;

            // try right
            bool foundRight = false;
            for (auto r: remaining_tiles)
            {
                if (r.second.edges.left == tile.edges.right)
                {
                    std::cout << "Found possible right: " << tile.id << std::endl;
                    image[0][1] = r.second.id;
                    remaining_tiles.erase(r.second.id);
                    foundRight = true; 
                    break;
                }
                else
                {
                    std::cout << tile.edges.right << "!=" << r.second.edges.left << std::endl;
                }
            }

            if (!foundRight)
            {
                std::cout << "No match for " << tile.id << "!" << std::endl;
                Tile flipped = flip(tile);
                print_tile(flipped);
            }

            tile = flip(tile);
            image[0][0] = tile.id;

            // try right
            foundRight = false;
            for (auto r: remaining_tiles)
            {
                if (r.second.edges.left == tile.edges.right)
                {
                    std::cout << "Found possible right: " << r.second.id << std::endl;
                    image[0][1] = r.second.id;
                    remaining_tiles.erase(r.second.id);
                    foundRight = true; 
                    break;
                }
                else
                {
                    std::cout << tile.edges.right << "!=" << r.second.edges.left << std::endl;
                }
            }

            exit(1);

            std::cout << "Size: " << remaining_tiles.size() << std::endl;
        }

        break;
    }
    
}

int main()
{
    std::vector<std::string> lines = get_lines("../day20.txt");
    std::vector<Tile> tiles;
    get_tiles(lines, tiles);
    reorder(tiles);


    std::cout << "Num lines: " << lines.size() << std::endl;
    std::cout << "Num tiles: " << tiles.size() << std::endl;

    return 0;
}