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
    NO_DUPLICATE,   // There were no consecutively repeated digits in password.
    DIGIT_DECREASED // A digit decreased relative to previous digit.
};


std::pair<bool, Error> validate_password(int password)
{
    std::string password_string = std::to_string(password);


    int  last_digit      = -1;
    bool duplicate_digit = false;

    for (char c : password_string)
    {
        int i = std::stoi(&c);

        if (i < last_digit)
            return std::pair<bool, Error>(false, DIGIT_DECREASED);

        if (i == last_digit)
            duplicate_digit = true;

        last_digit = i;
    }


    if (duplicate_digit)
        return std::pair<bool, Error>(true, ACCEPT);

    else
        return std::pair<bool, Error>(false, NO_DUPLICATE);
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
