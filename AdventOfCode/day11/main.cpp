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

enum Symbol {
    FLOOR,
    EMPTY,
    OCCUPIED
};

void print_chairs(std::vector<std::vector<Symbol>> chairs)
{
    int occupied = 0;
    int empty = 0;
    int floor = 0;
    for (auto row: chairs) {
        for (auto col: row) {
            if (col == Symbol::FLOOR) { floor++; }
            if (col == Symbol::EMPTY) { empty++; }
            if (col == Symbol::OCCUPIED) { occupied++; }
        }
    }

    std::cout << "Floor: " << floor << ", " << "Empty: " << empty << ", " << "Occupied: " << occupied << std::endl;
}

bool equal(std::vector<std::vector<Symbol>> chairs1, std::vector<std::vector<Symbol>> chairs2)
{
    bool chairsEqual = true;
    for (int i = 0; i < chairs1.size(); ++i)
    {
        for (int j = 0; j < chairs1[i].size(); ++j)
        {
            if (chairs1[i][j] != chairs2[i][j])
            {
                chairsEqual = false;
                break;
            }
        }
    }

    return chairsEqual;
}

bool isValid(const std::vector<std::vector<Symbol>>& chairs, int i, int j)
{
    return (i >= 0 && i < chairs.size()) && (j >= 0 && j < chairs[0].size());
}

int countAdjacent(const std::vector<std::vector<Symbol>>& chairs, int i, int j)
{
    int count = 0;
    for (int k = -1; k <= 1; ++k)
    {
        for (int l = -1; l <= 1; ++l)
        {
            if (!(k == 0 && l == 0) && isValid(chairs, i + k, j + l))
            {
                if (chairs[i + k][j + l] == Symbol::OCCUPIED)
                {
                    count++;
                }
            }
        }
    }

    return count;
}

void step(std::vector<std::vector<Symbol>>& chairs)
{
    std::vector<std::vector<Symbol>> chairs_next;
    for (int i = 0; i < chairs.size(); ++i)
    {
        std::vector<Symbol> new_row;
        chairs_next.push_back(new_row);
        for (int j = 0; j < chairs[i].size(); ++j)
        {
            if (chairs[i][j] == Symbol::EMPTY && (countAdjacent(chairs, i, j) == 0))
            {
                chairs_next[i].push_back(Symbol::OCCUPIED);
            }
            else if (chairs[i][j] == Symbol::OCCUPIED && (countAdjacent(chairs, i, j) >= 4))
            {
                chairs_next[i].push_back(Symbol::EMPTY);
            }
            else
            {
                chairs_next[i].push_back(chairs[i][j]);
            }
            
        }
    }

    std::swap(chairs, chairs_next);
}

void simulate(std::vector<std::vector<Symbol>> chairs)
{
    std::vector<std::vector<Symbol>> prev;
    int steps = 0;
    do {
        prev = chairs;
        step(chairs);
        steps++;
    } while(!equal(chairs, prev));
    print_chairs(chairs);
    std::cout << "Num steps: " << steps << std::endl;
}

int main()
{
    std::vector<std::string> lines = get_lines("../day11.txt");
    std::vector<std::vector<Symbol>> chairs;
    std::transform(lines.begin(), lines.end(), std::back_inserter(chairs), [](std::string line) {
        
        std::vector<Symbol> symbols;
        for (int i = 0; i < line.size(); ++i)
        {
            switch (line[i])
            {
                case '.':
                    symbols.push_back(Symbol::FLOOR);
                    break;
                case 'L':
                    symbols.push_back(Symbol::EMPTY);
                    break;
                case '#':
                    symbols.push_back(Symbol::OCCUPIED);
                    break;
            }
        }
        return symbols;
    });

    simulate(chairs);

    std::cout << "Adjacent: " << countAdjacent(chairs, 6, 7) << std::endl;
    std::cout << "Equal: " << equal(chairs, chairs) << std::endl;

    std::cout << "Num rows: " << chairs.size() << std::endl;
    std::cout << "Num lines: " << lines.size() << std::endl;

    return 0;
}