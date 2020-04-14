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

void changeSlashes(std::string& input)
{
	for (char& c : input)
	{
		if (c == '/')
			c = '\\';
	}
}

bool pathToDirectoryExists(const std::filesystem::path& path)
{
	std::string path_string = path.u8string();

	for (char c : path_string)
	{
		//Banned symbols for naming in windows
		if (c == '<' || c == '>' || c == '"' || c == '|' || c == '?' || c == '*')
			return 0;
	}

	//This is made to prevent exceptions
	bool res;
	try
	{
		res = std::filesystem::exists(path);

		//The if part is made to combat the paths which have only empty characters or only dots
		//with empty characters, the system would return that there exists such path when it does not
		//so I just try to iterate over that path that should be a directory and if I get an exception
		//the path does not exist
		if (std::filesystem::is_directory(path))
			auto i = std::filesystem::recursive_directory_iterator(path);
	}
	catch (...)
	{
		return 0;
	}
	if (!std::filesystem::is_directory(path))
		return false;

	return res;
}

bool canUserEnterDirectory(const std::filesystem::path& path, const std::string& username)
{
	std::string startingPath = "C:\\oosproject\\users\\" + username;
	std::string path_string = path.u8string();

	if (path_string.length() < startingPath.length())
		return 0;

	for (int i = 0; i < (int)startingPath.length(); ++i)
		if (startingPath[i] != path_string[i])
			return 0;

	return 1;
}