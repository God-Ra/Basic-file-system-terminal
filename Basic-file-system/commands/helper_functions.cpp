#include "helper_functions.h"

void splitStringIntoWords(std::vector<std::string>& wordList, std::string inputString)
{
	std::string currentWord = "";
	for (char c : inputString)
	{
		if (c == ' ')
		{
			if (currentWord.length() != 0)
				wordList.push_back(currentWord);
			currentWord = "";
		}
		else
			currentWord += c;
	}

	if (currentWord.length() != 0)
		wordList.push_back(currentWord);
}

void parseInputLine(std::vector<std::string>& wordList, const std::string& inputString)
{
	wordList.clear();
	std::string currentWord = "";
	bool quotationMarkHappened = false;

	for (char c : inputString)
	{
		if (c == '\"')
		{
			if (quotationMarkHappened)
			{
				if (currentWord.length() != 0)
					wordList.push_back(currentWord);
				currentWord = "";
				quotationMarkHappened = false;
			}
			else
				quotationMarkHappened = true;
		}
		else if (c == ' ' && !quotationMarkHappened)
		{
			if (currentWord.length() != 0)
				wordList.push_back(currentWord);
			currentWord = "";
		}
		else if ((c == ' ' && quotationMarkHappened) || (c != ' '))
			currentWord += c;
	}

	if (quotationMarkHappened) throw std::exception("The quotation mark is not closed");

	if (currentWord.length() != 0)
		wordList.push_back(currentWord);
}