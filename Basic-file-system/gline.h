#pragma once
#include "constants.h"
#include <string>
#include <iostream>
#include <conio.h>

/*
==============
getLine

startingLine - The string preceding input in the console
MAX_LENGTH - The maximum length of the input
line - The function result is returned using this string, the reason the output is returned over a reference
is performance improvement over plainly returning and copying std::string
==============
*/
void getLine(std::string& line, const int MAX_LENGTH, const std::string& startingLine);

/*
==============
getLineAsterisks

For each input character an asterisk is printed

startingLine - The string preceding input in the console
MAX_LENGTH - The maximum length of the input
line - The function result is returned using this string, the reason the output is returned over a reference
is performance improvement over plainly returning and copying std::string
==============
*/
void getLineAsterisks(std::string& line, const int MAX_LENGTH, const std::string& startingLine);