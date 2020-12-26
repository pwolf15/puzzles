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
#include <queue>

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

void print_image(const std::vector<std::vector<int>> image)
{
    for (size_t i = 0; i < image.size(); ++i)
    {
        for (size_t j = 0; j < image[0].size(); ++j)
        {
            std::cout << image[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
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

std::vector<std::vector<int>> initialize_image(int size)
{
    std::vector<std::vector<int>> image;
    for (int i = 0; i < size; i++)
    {
        std::vector<int> image_row;
        for (int j = 0; j < size; j++)
        {
            image_row.push_back(-1);
        }
        image.push_back(image_row);
    }

    return image;
}

bool is_valid(int x, int y, int w, int h)
{
    return (x < w && x >= 0) && (y < h && y >= 0);
}

bool get_next_tile(int x, int y, int& next_x, int& next_y)
{
    if (is_valid(x + 1, y, 3, 3))
    {
        next_x = x + 1;
        next_y = y;
        return true;
    }
    if (is_valid(0, y + 1, 3, 3))
    {
        next_x = 0;
        next_y = y + 1;
        return true;
    }
    return false;
}   

bool validate_image(const std::vector<std::vector<int>>& current_image, std::unordered_map<int, Tile> tiles)
{
    bool valid = true;
    for (int i = 0; i < current_image.size(); ++i)
    {
        for (int j = 0; j < current_image[0].size(); ++j)
        {
            // ecah direction
            std::vector<std::pair<int, int>> offsets = {{1, 0}, { -1, 0}, { 0, 1 }, { 0, - 1}};

            int tileId = current_image[i][j];
            if (tileId == -1) continue;

            Tile tile = tiles[tileId];

            for (auto offset: offsets)
            {
                int pos_x = j + std::get<0>(offset);
                int pos_y = i + std::get<1>(offset);

                if (is_valid(pos_x, pos_y, 3, 3))
                {
                    if (current_image[pos_y][pos_x] == -1) continue;
                    
                    int neighborTileId = current_image[pos_y][pos_x];
                    Tile neighorTile   = tiles[neighborTileId];
                    int neighbor_top = neighorTile.edges.top;
                    int neighbor_bottom = neighorTile.edges.bottom;
                    int neighbor_left = neighorTile.edges.left;
                    int neighbor_right = neighorTile.edges.right;

                    if (pos_x == 1 && pos_y == 0)
                    {
                        if (neighbor_left != tile.edges.right) return false;
                    }
                    else if (pos_x == -1 && pos_y == 0)
                    {
                        if (neighbor_right != tile.edges.left) return false;
                    }
                    else if (pos_x == 0 && pos_y == 1)
                    {
                        if (neighbor_bottom != tile.edges.top) return false;
                    }
                    else if (pos_x == 0 && pos_y == -1)
                    {
                        if (neighbor_top != tile.edges.bottom) return false;
                    }
                }
                else
                {
                    continue;
                }
            }
        }
    }

    return true;
}

static int count = 0;

bool test_config(std::vector<std::vector<int>> current_image, std::queue<std::pair<int, int>> pos_queue, std::unordered_map<int, Tile> remaining_tiles, const std::unordered_map<int, Tile>& tiles)
{
    // int nextX, nextY;
    // get_next_tile(x, y, nextX, intY);

    // for (auto tile: remaining_tiles)
    // {
    //     image[x][y] = tile.first;

    //     if (test_config(image, nextX, nextY, tile.first, remaining_tiles)) break;
    // }

    ++count;

    if (pos_queue.empty()) { return true; }

    std::pair<int, int> pos = pos_queue.front();
    pos_queue.pop();

    bool valid = true;

    for (auto tilePair: remaining_tiles)
    {
        current_image[std::get<0>(pos)][std::get<1>(pos)] = tilePair.first;
        auto remaining_tiles_new = remaining_tiles;
        remaining_tiles_new.erase(tilePair.first);

        // std::cout << "Remaining tiles: " << remaining_tiles_new.size() << std::endl;

        if (validate_image(current_image, tiles))
        {
            print_image(current_image);
            test_config(current_image, pos_queue, remaining_tiles_new, tiles);
        }

        // else if validate image flipped
    }

    if (count % 100000 == 0) { std::cout << "Counts: " << count << std::endl; }

    return false;
}

void find_correct_order(std::vector<Tile> tiles)
{
    std::vector<std::vector<int>> image = initialize_image(3);
    std::unordered_map<int, Tile> remaining_tiles;
    for (auto tile: tiles)
    {
        remaining_tiles[tile.id] = tile;
    }
    std::unordered_map<int, Tile> tile_map = remaining_tiles;

    // 1. start with 0, 0
    // 2. try assuming first tile is 0, 0
    // 3. try second tile (if matches with all current tiles, advance to next item)
    // 4. if next tile fails, go back, try rotating/flipping tile

    int x = 0;
    int y = 0;
    int nextX, nextY;
    std::queue<std::pair<int, int>> pos_queue;
    pos_queue.push({0, 0});

    while (get_next_tile(x, y, nextX, nextY))
    {
        pos_queue.push({ nextX, nextY });
        x = nextX;
        y = nextY;
    }

    std::cout << "Tiles: " << tiles.size() << std::endl;
    test_config(image, pos_queue, remaining_tiles, tile_map);

    std::cout << "Counts: " << count << std::endl;
}

int main()
{
    std::vector<std::string> lines = get_lines("../day20.txt");
    std::vector<Tile> tiles;
    get_tiles(lines, tiles);
    find_correct_order(tiles);

    std::cout << "Num lines: " << lines.size() << std::endl;
    std::cout << "Num tiles: " << tiles.size() << std::endl;

    return 0;
}