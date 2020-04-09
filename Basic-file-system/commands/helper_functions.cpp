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