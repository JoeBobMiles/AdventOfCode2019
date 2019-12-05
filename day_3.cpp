/**
 * @file day_3.cpp
 * @author Joseph R Miles <me@josephrmiles.com>
 * @date 2019-12-03
 *
 * https://adventofcode.com/2019/day/3
 *
 * This is the solution to the 2019 Advent of Code Day 3 challenge. For this
 * challenge, we have to create a program that will draw out two wires and map
 * out all intersection points. Then we will measure the distance between these
 * points and the central starting point of the wire. The shortest distance is
 * our goal.
 */


#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <climits>


typedef std::pair<char,int> Command;
typedef std::pair<int,int>  Cell;


std::vector<Command> parse_command_string(std::string command_string)
{
    std::vector<Command> commands;
    std::string          buffer;


    for (auto cursor = command_string.begin();
         cursor < command_string.end();
         cursor++)
    {
        char c = (char) *cursor;

        if (c != ',')
            buffer.push_back(c);

        else
        {
            char command   = buffer[0];
            int  parameter = std::stoi(buffer.substr(1));

            commands.push_back(Command(command, parameter));

            buffer.erase();
        }
    }


    // Because the last command ends with the end of the string, we need
    // to do one-last push-back into the vector of commands.
    char command   = buffer[0];
    int  parameter = std::stoi(buffer.substr(1));

    commands.push_back(Command(command, parameter));


    return commands;
}


std::vector<Cell> build_wire(std::vector<Command> commands)
{
    std::vector<Cell> wire;


    int x = 0, y = 0;

    for (Command command : commands)
    {
        // std::cout << command.first << command.second << std::endl;

        if (command.first == 'L')
        {
            for (int i = 0; i < command.second; i++)
                wire.push_back(Cell(--x, y));
        }
        else if (command.first == 'R')
        {
            for (int i = 0; i < command.second; i++)
                wire.push_back(Cell(++x, y));
        }
        else if (command.first == 'U')
        {
            for (int i = 0; i < command.second; i++)
                wire.push_back(Cell(x, ++y));
        }
        else if (command.first == 'D')
        {
            for (int i = 0; i < command.second; i++)
                wire.push_back(Cell(x, --y));
        }
    }


    return wire;
}


void print_cells(std::vector<Cell> cells)
{
    for (Cell cell : cells)
        std::cout << cell.first << ',' << cell.second << ' ';

    std::cout << std::endl;
}

int main (int argc, const char** argv)
{
    std::ifstream file;
    file.open(argv[1], std::ios::in);


    std::string wire1_command_string;
    std::string wire2_command_string;

    std::getline(file, wire1_command_string);
    std::getline(file, wire2_command_string);


    file.close();


    std::vector<Cell> wire1 = build_wire(parse_command_string(wire1_command_string));
    std::vector<Cell> wire2 = build_wire(parse_command_string(wire2_command_string));


    // `intersections` was empty until we sorted both cell arrays...
    // When I tried that last night, it didn't work...
    std::sort(wire1.begin(), wire1.end());
    std::sort(wire2.begin(), wire2.end());


    // print_cells(wire1);
    // print_cells(wire2);


    std::vector<Cell> intersections;


    std::set_intersection(wire1.begin(), wire1.end(),
                          wire2.begin(), wire2.end(),
                          std::back_inserter(intersections));


    print_cells(intersections);


    int minimum_manhattan = INT_MAX;
#define manhattan(p) (std::abs(p.first) + std::abs(p.second))

    for (Cell cell : intersections)
        minimum_manhattan = manhattan(cell) < minimum_manhattan ? manhattan(cell) : minimum_manhattan;


    std::cout << "Result:\t" << minimum_manhattan << std::endl;


    return 0;
}
