#include "gline.h"

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