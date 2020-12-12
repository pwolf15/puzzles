#include "assembly_parser.hpp"
#include <algorithm>
#include <fstream>
#include <unordered_set>
#include <stack>

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

int get_accumulator(std::string filename)
{
    return 0;
}

int find_accumulator(std::vector<Instruction> instructions)
{
    int counter = 0;
    int accumulator = 0;
    std::unordered_set<int> visited_instructions;

    while (true)
    {
        Instruction instruction = instructions[counter];
        if ((visited_instructions.find(counter) != visited_instructions.end()))
        {
            return accumulator;
        }

        visited_instructions.insert(counter);

        switch (instruction.op)
        {
            case Op::ACC:
            {
                int val = std::stoi(instruction.arg.substr(1));
                int sign = instruction.arg[0] == '+' ? 1 : -1;
                accumulator += sign * val;
                counter++;
            }
            break;

            case Op::NOP:
            {
                counter++;
            }
            break;

            case Op::JMP:
            {
                int dir = instruction.arg[0] == '+' ? 1 : -1;
                int val = std::stoi(instruction.arg.substr(1));
                counter += dir * val;
            }
            break;
        }
    }
}

std::pair<int, bool> find_accumulator_terminates(std::vector<Instruction> instructions)
{
    int counter = 0;
    int accumulator = 0;
    std::unordered_set<int> visited_instructions;

    while (true)
    {
        if (counter >= instructions.size())
        {
            std::cout << "HERE2" << std::endl;
            std::cout << "Accumulator: " << accumulator << std::endl;
            break;
        }

        Instruction instruction = instructions[counter];
        if ((visited_instructions.find(counter) != visited_instructions.end()))
        {
            return { false, accumulator };
        }

        visited_instructions.insert(counter);

        switch (instruction.op)
        {
            case Op::ACC:
            {
                int val = std::stoi(instruction.arg.substr(1));
                int sign = instruction.arg[0] == '+' ? 1 : -1;
                accumulator += sign * val;
                counter++;
            }
            break;

            case Op::NOP:
            {
                counter++;
            }
            break;

            case Op::JMP:
            {
                int dir = instruction.arg[0] == '+' ? 1 : -1;
                int val = std::stoi(instruction.arg.substr(1));
                counter += dir * val;
            }
            break;
        }
    }

    return { true, accumulator };
}

int main()
{
    std::string line;

    std::vector<std::string> lines = get_lines("../day08.txt"); // get lines of file
    std::vector<Instruction> instructions;

    auto get_op = [](std::string stringOp) {
        if (stringOp == "acc") return Op::ACC;
        if (stringOp == "jmp") return Op::JMP;
        if (stringOp == "nop") return Op::NOP;
        return Op::NOP;
    };

    std::transform(lines.begin(), lines.end(), std::back_inserter(instructions), [&](const std::string& line) {
        Instruction instruction;
        instruction.op = get_op(line.substr(0, line.find(" ")));
        instruction.arg = line.substr(line.find(" ") + 1);
        return instruction;
    });

    for (int i = 0; i < instructions.size(); ++i)
    {
        std::pair<bool, int> result = find_accumulator_terminates(instructions);
        if (result.first)
        {
            break;
        }

        Instruction test;
        test.arg = instructions[i].arg;
        Instruction temp = instructions[i];
        if (instructions[i].op == Op::NOP) 
        {
            test.op = Op::JMP;
        }
        else if (instructions[i].op == Op::JMP)
        {
            test.op = Op::NOP;
        }

        instructions[i] = test;
        result = find_accumulator_terminates(instructions);
        // if (result.first)
        // {
        //     break;
        // }
        // else
        // {
            instructions[i] = temp;
        //}       
    }

    std::cout << "HERE!" << std::endl;

    return 0;
}