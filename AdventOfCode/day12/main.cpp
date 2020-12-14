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

enum OpCode
{
    NORTH,
    SOUTH,
    EAST,
    WEST,
    FORWARD,
    LEFT,
    RIGHT
};

struct Instruction
{
    OpCode op;
    int arg;
};

int computeManhattanDistance(std::vector<Instruction> instructions)
{
    int ver = 0;
    int hor = 0;
    int dir = OpCode::EAST;

    for (size_t i = 0; i < instructions.size(); ++i)
    {
        Instruction instruction = instructions[i];
        switch (instruction.op)
        {
            case OpCode::FORWARD:
            {
                if (dir == OpCode::EAST)
                {
                    hor += instruction.arg;
                }
                else if (dir == OpCode::WEST)
                {
                    hor -= instruction.arg;
                }
                else if (dir == OpCode::NORTH)
                {
                    ver += instruction.arg;
                }
                else if (dir == OpCode::SOUTH)
                {
                    ver -= instruction.arg;
                }
            }
            break;

            case OpCode::RIGHT:
            {
                if (instruction.arg == 90)
                {
                    if (dir == OpCode::NORTH) dir = OpCode::EAST;
                    else if (dir == OpCode::EAST) dir = OpCode::SOUTH;
                    else if (dir == OpCode::SOUTH) dir = OpCode::WEST;
                    else if (dir == OpCode::WEST) dir = OpCode::NORTH;
                }
                else if (instruction.arg == 180)
                {
                    if (dir == OpCode::NORTH) dir = OpCode::SOUTH;
                    else if (dir == OpCode::EAST) dir = OpCode::WEST;
                    else if (dir == OpCode::SOUTH) dir = OpCode::NORTH;
                    else if (dir == OpCode::WEST) dir = OpCode::EAST;
                }
                else if (instruction.arg == 270)
                {
                    if (dir == OpCode::NORTH) dir = OpCode::WEST;
                    else if (dir == OpCode::EAST) dir = OpCode::NORTH;
                    else if (dir == OpCode::SOUTH) dir = OpCode::EAST;
                    else if (dir == OpCode::WEST) dir = OpCode::SOUTH;
                }
            }
            break;

            case OpCode::LEFT:
            {
                if (instruction.arg == 90)
                {
                    if (dir == OpCode::NORTH) dir = OpCode::WEST;
                    else if (dir == OpCode::EAST) dir = OpCode::NORTH;
                    else if (dir == OpCode::SOUTH) dir = OpCode::EAST;
                    else if (dir == OpCode::WEST) dir = OpCode::SOUTH;
                }
                else if (instruction.arg == 180)
                {
                    if (dir == OpCode::NORTH) dir = OpCode::SOUTH;
                    else if (dir == OpCode::EAST) dir = OpCode::WEST;
                    else if (dir == OpCode::SOUTH) dir = OpCode::NORTH;
                    else if (dir == OpCode::WEST) dir = OpCode::EAST;
                }
                else if (instruction.arg == 270)
                {
                    if (dir == OpCode::NORTH) dir = OpCode::EAST;
                    else if (dir == OpCode::EAST) dir = OpCode::SOUTH;
                    else if (dir == OpCode::SOUTH) dir = OpCode::WEST;
                    else if (dir == OpCode::WEST) dir = OpCode::NORTH;
                }
            }
            break;

            case OpCode::EAST:
            {
                hor += instruction.arg;
            }
            break;

            case OpCode::WEST:
            {
                hor -= instruction.arg;
            }
            break;

            case OpCode::NORTH:
            {
                ver += instruction.arg;
            }
            break;

            case OpCode::SOUTH:
            {
                ver -= instruction.arg;
            }
            break;
        }
    }

    std::cout << "Vertical: " << ver << std::endl;
    std::cout << "Horizontal: " << hor << std::endl;
    std::cout << "Manhattan distance: " << std::abs(ver) + std::abs(hor) << std::endl;

    return 0;
}

int main()
{
    std::vector<std::string> lines = get_lines("../day12.txt");
    std::vector<Instruction> instructions;

    std::transform(lines.begin(), lines.end(), std::back_inserter(instructions), [](std::string line) {

        Instruction i;
        switch(line[0])
        {
            case 'N':
                i.op = OpCode::NORTH;
                break;
            case 'S':
                i.op = OpCode::SOUTH;
                break;
            case 'E':
                i.op = OpCode::EAST;
                break;
            case 'W':
                i.op = OpCode::WEST;
                break;
            case 'R':
                i.op = OpCode::RIGHT;
                break;
            case 'L':
                i.op = OpCode::LEFT;
                break;
            case 'F':
                i.op = OpCode::FORWARD;
                break;
        }

        i.arg = std::stoi(line.substr(1));

        return i;
    });

    computeManhattanDistance(instructions);

    std::cout << "Num instructions: " << instructions.size() << std::endl;
    std::cout << "Num lines: " << lines.size() << std::endl;

    return 0;
}