#ifndef ASSEMBLY_PARSER_HPP
#define ASSEMBLY_PARSER_HPP

#include <vector>
#include <string>
#include <iostream>

enum Op 
{
    NOP = 0,
    ACC,
    JMP
};

struct Instruction
{
    Op op;
    std::string arg;
};

// Instruction get_instruction(const std::string& serial_instruction)
// {
//     Instruction instruction;

//     return instruction;
// }

#endif