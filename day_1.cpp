/**
 * @file day_2.cpp
 * @author Joseph R Miles
 * @date 2019-12-01
 *
 * This is the Advent of Code 2019 Day 2 Challenge.
 */

#include <iostream>
#include <fstream>
#include <string>


#define MASS_TO_FUEL(M) (((int) (M / 3)) - 2)


int compute_fuel(int mass)
{
    int fuel = MASS_TO_FUEL(mass);

    if (fuel > 0)
        return fuel + compute_fuel(fuel);

    else
        return 0;
}


int main (int argc, const char **argv)
{
    // For this part of the challenge, we need to take into account the fuel
    // that is need to carry our fuel. This is a recursive relation.

    int total_fuel = 0;


    std::ifstream input;
    input.open(argv[1], std::ios::in);

    std::string line;


    while (std::getline(input, line))
    {
        total_fuel += compute_fuel(std::stoi(line));
    }

    std::cout << "TOTAL FUEL:\t" << total_fuel << std::endl;

    return 0;
}
