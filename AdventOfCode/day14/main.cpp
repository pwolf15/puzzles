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


struct Load
{
    uint64_t addr;
    uint64_t val;
};

struct InstructionSet
{
    uint64_t bit_mask;
    uint64_t bit_mask_value;
    std::vector<Load> load_instructions;
};

void get_instructions(std::vector<std::string> lines, std::vector<InstructionSet>& instructions)
{
    std::vector<Load> loads;
    uint64_t bit_mask = 0;
    uint64_t bit_mask_value = 0;
    int count = 0;
    std::vector<Load> load_instructions;
    for (auto line: lines)
    {
        if (line.substr(0, 4) == "mask")
        {
            if (count > 0)
            {
                InstructionSet iset;
                iset.bit_mask = bit_mask;
                iset.bit_mask_value = bit_mask_value;
                iset.load_instructions = load_instructions;
                instructions.push_back(iset);
                load_instructions.clear();
            }

            std::string mask = line.substr(7);
            bit_mask = 0;
            bit_mask_value = 0;
            for (int i = 0; i < 36; ++i)
            {
                if (mask[i] == 'X')
                {
                    continue;
                }

                bit_mask |= ((uint64_t)1 << (36 - i - 1));
                bit_mask_value |= ((uint64_t)(mask[i] - '0') << (36 - i - 1));
            }

        }
        else
        {
            Load load;
            std::string address = line.substr(line.find("[") + 1, line.find("]") - (line.find("[") + 1));
            load.addr = std::stoi(address);
            load.val = std::stoi(line.substr(line.find("=") + 1));
            load_instructions.push_back(load);
        }

        count++;
    }

    InstructionSet iset;
    iset.bit_mask = bit_mask;
    iset.bit_mask_value = bit_mask_value;
    iset.load_instructions = load_instructions;
    instructions.push_back(iset);
    load_instructions.clear();
}

int main()
{
    std::vector<std::string> lines = get_lines("../day14.txt");
    std::vector<InstructionSet> instruction_set;
    get_instructions(lines, instruction_set);

    std::cout << "Num lines: " << lines.size() << std::endl;
    std::cout << "Num instruction set: " << instruction_set.size() << std::endl;

    return 0;
}