/**
 * @file day_4.cpp
 * @author Joseph R Miles
 * @date 2019-12-04
 *
 * This is the solution for Advent of Code 2019 Day 4 challenge:
 * https://adventofcode.com/2019/day/4
 */


#include <iostream>
#include <string>
#include <vector>


enum Error {
    ACCEPT,         // We didn't error.
    NO_RUN_OF_TWO,   // There was no "run" of 2 digits.
    DIGIT_DECREASED // A digit decreased relative to previous digit.
};


std::pair<bool, Error> validate_password(int password)
{
    std::string password_string = std::to_string(password);


    int last_digit = -1;
    int digit_count[10] = { 0 };


    for (char c : password_string)
    {
        int i = std::stoi(&c);


        if (i < last_digit)
            return std::pair<bool, Error>(false, DIGIT_DECREASED);

        digit_count[i]++;

        last_digit = i;
    }


    for (int i : digit_count)
    {
        if (i == 2)
            return std::pair<bool, Error>(true, ACCEPT);
    }


    return std::pair<bool, Error>(false, NO_RUN_OF_TWO);
}


int main()
{
    std::pair<int,int> input(278384, 824795);


    std::vector<int> possible_passwords;


    for (int password = input.first; password <= input.second; password++)
    {
        std::pair<bool, Error> result = validate_password(password);

        if (result.first == true)
            possible_passwords.push_back(password);
    }


    std::cout << "Result:\t" << possible_passwords.size() << std::endl;


    return 0;
}
