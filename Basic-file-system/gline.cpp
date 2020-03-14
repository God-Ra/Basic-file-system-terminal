#include "gline.h"

/*
==============
getLine

startingLine - The string that will be output before taking the input
MAX_LENGTH - The maximum length of the line taking the input, takes into account the length of startingLine
line - The function returns the input through this string, the reason the output is returned via
a parameter is to not create a copy when returning a std::string directly
==============
*/
void getLine(std::string& line, const int MAX_LENGTH, const std::string& startingLine)
{
	line = "";
	std::cout << startingLine;
	char c;
	do
	{
		c = _getch();
		if (c == ASCII_BACKSPACE)
		{
			if (line.length())
				line.pop_back();

			std::cout << "\r" << std::string(line.length() + startingLine.size() + 10, ' ');
			std::cout << "\r";
			std::cout << startingLine;
			std::cout << line;
		}
		else if (c != ASCII_ENTER && (int)line.length() < MAX_LENGTH)
		{
			line += c;
			std::cout << c;
		}
	} while (c != ASCII_ENTER);
	std::cout << "\n";
}

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
void getLineAsterisks(std::string& line, const int MAX_LENGTH, const std::string& startingLine)
{
	line = "";
	std::cout << startingLine;
	char c;
	do
	{
		c = _getch();
		if (c == ASCII_BACKSPACE)
		{
			if (line.length())
				line.pop_back();

			std::cout << "\r" << std::string(line.length() + startingLine.size() + 10, ' ');
			std::cout << "\r";
			std::cout << startingLine;
			std::cout << std::string(line.length(), '*');
		}
		else if (c != ASCII_ENTER && (int)line.length() < MAX_LENGTH)
		{
			line += c;
			std::cout << "*";
		}
	} while (c != ASCII_ENTER);
	std::cout << "\n";
}