/**
 * @file day_2.cpp
 * @author Joseph R Miles <me@josephrmiles.com>
 * @date 2019-12-02
 *
 * This is the second day of the Advent of Code 2019 challenge.
 *
 * We are making a simple emulator for the Elve's Intcode architecture.
 *
 * It's much like the SUBLEQ emulator, except we have opcodes. Three to be
 * exact: 1, 2, 99. These function as follows:
 *  - Opcode 1 has 3 parameters. The first is the location of where the first
 *    operand is stored. The second is the location where the second
 *    operand is stored. The third is the position where the result of ADDING
 *    the first and second operands is stored.
 *  - Opcode 2 has 3 parameters. The first and second are the locations where
 *    the first and second operands are stored, respectively. The third is the
 *    position where the result of MULTIPLYING the first and second operands is
 *    stored.
 *  - Opcode 99 tells the program to exit.
 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>


std::vector<int> read_program(const char* input_file_name)
{
    std::ifstream input;
    input.open(input_file_name, std::ios::in);

    std::string code;
    std::getline(input, code);

    std::string      data;
    std::vector<int> program;


    auto begin = code.begin();
    auto end   = code.end();

    for (auto cursor = begin;
         cursor < end;
         cursor++)
    {
        char c = (char) *cursor;

        if (c != ',')
            data.push_back((char) *cursor);

        else
        {
            program.push_back(std::stoi(data));
            data.erase();
        }
    }

    return program;
}


int execute_program(std::vector<int> program, int noun, int verb)
{
    // Restore program to the user's desired state.
    program[1] = noun;
    program[2] = verb;


    int offset = 0, opcode, a, b, c;

    do
    {
        opcode = program[offset++];
        a      = program[offset++];
        b      = program[offset++];
        c      = program[offset++];

        if (opcode == 1)
        {
            program[c] = program[a] + program[b];
        }
        else if (opcode == 2)
        {
            program[c] = program[a] * program[b];
        }
        else if (opcode == 99)
        {
            break;
        }
        else
        {
            std::cout << "Something\'s wrong! Read opcode: " << opcode << std::endl;
        }
    } while (opcode != 99);

    return program[0];
}


int main (int argc, const char** argv)
{
    std::vector<int> program = read_program(argv[1]);

    for (int noun = 0; noun <= 99; noun++)
    {
        for (int verb = 0; verb <= 99; verb++)
        {
            int result = execute_program(program, noun, verb);

            if (result == 19690720)
            {
                std::cout << "Solution:\t" << ((100 * noun) + verb) << std::endl;
                break;
            }
        }
    }

    return 0;
}
