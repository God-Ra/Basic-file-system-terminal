#pragma once
#include "constants.h"
#include <string>
#include <iostream>
#include <conio.h>

/*
==============
getLine (TESTED)

startingLine - The string that will be output before taking the input
MAX_LENGTH - The maximum length of the line taking the input, takes into account the length of startingLine
line - The function returns the input through this string, the reason the output is returned via
a parameter is to not create a copy when returning a std::string directly
==============
*/
void getLine(std::string& line, const int MAX_LENGTH, const std::string& startingLine);

/*
==============
getLineAsterisks

The function outputs an asterisk for each character in the input

startingLine - The string that will be output before taking the input
MAX_LENGTH - The maximum length of the line taking the input, takes into account the length of startingLine
line - The function returns the input through this string, the reason the output is returned via
a parameter is to not create a copy when returning a std::string directly
==============
*/
void getLineAsterisks(std::string& line, const int MAX_LENGTH, const std::string& startingLine);