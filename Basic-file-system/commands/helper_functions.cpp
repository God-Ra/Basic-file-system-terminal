#include "helper_functions.h"

void parseInputLine(std::vector<std::string>& wordList, const std::string& inputString)
{
	wordList.clear();
	std::string currentWord = "";
	bool quotationMarkOccurred = false;

	for (char c : inputString)
	{
		if (c == '\"')
		{
			if (quotationMarkOccurred)
			{
				if (currentWord.length() != 0)
					wordList.push_back(currentWord);
				currentWord = "";
				quotationMarkOccurred = false;
			}
			else
				quotationMarkOccurred = true;
		}
		else if (c == ' ' && !quotationMarkOccurred)
		{
			if (currentWord.length() != 0)
				wordList.push_back(currentWord);
			currentWord = "";
		}
		else if ((c == ' ' && quotationMarkOccurred) || (c != ' '))
			currentWord += c;
	}

	if (quotationMarkOccurred) throw std::exception("The quotation mark is not closed");

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

	bool res;
	try
	{
		res = std::filesystem::exists(path);

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

bool pathToFileExists(const std::filesystem::path& path)
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

		if (std::filesystem::is_directory(path))
			auto i = std::filesystem::recursive_directory_iterator(path);
	}
	catch (...)
	{
		return 0;
	}

	return res;
}

bool canUserAccessFile(const std::filesystem::path& path, const std::string& username)
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