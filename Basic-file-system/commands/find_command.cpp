#include "find_command.h"

FindCommand::FindCommand(const std::vector<std::string>& argumentList)
{
	this->argumentList = argumentList;
}

void FindCommand::execute(std::filesystem::path& currentLocation, const std::string& username)
{
	setCommandStatus(currentLocation, username);

	switch (status)
	{
	case Status::READY:
		printSuccessMessage();
		break;
	case Status::TOO_MANY_ARGUMENTS:
		std::cout << "Command: \"" << COMMAND_NAME << "\", ERROR: There are too many arguments!\n";
		break;
	case Status::TOO_FEW_ARGUMENTS:
		std::cout << "Command: \"" << COMMAND_NAME << "\", ERROR: There are not enough arguments!\n";
		break;
	case Status::INVALID_PERMISSIONS_FILE_ACCESS:
		std::cout << "Command: \"" << COMMAND_NAME << "\", ERROR: You do not have permissions to access this file!\n";
		break;
	case Status::NO_FILE_PATH_FOUND:
		std::cout << "Command: \"" << COMMAND_NAME << "\", ERROR: The specified file is not found!\n";
		break;
	case Status::TEXT_NOT_FOUND:
		printTextNotFoundMessage();
		break;
	case Status::FILE_IS_DIRECTORY:
		std::cout << "Command: \"" << COMMAND_NAME << "\", ERROR: The specified file is a directory!\n";
		break;
	}
}

void FindCommand::printSuccessMessage()
{
	std::cout << "Command: \"" << COMMAND_NAME << "\", "
		<< "SUCCESS: Found pattern \"" << pattern << "\" on line " << lineOfOccurence << "!\n";
}

void FindCommand::printTextNotFoundMessage()
{
	std::cout << "Command: \"" << COMMAND_NAME << "\", "
		<< "ERROR: Could not find pattern \"" << pattern << "\"!\n";
}

void FindCommand::setCommandStatus(std::filesystem::path& currentLocation, const std::string& username)
{
	status = Status::READY;
	if (!argumentListSizeCorrect())
		return;
	decomposeArgumentList();

	std::filesystem::path relativePath = currentLocation / path;
	std::filesystem::path absolutePath = path;

	if (pathToFileExists(relativePath))
	{
		relativePath = std::filesystem::absolute(relativePath);
		if (canUserAccessFile(relativePath, username))
			path = relativePath;
		else
			status = Status::INVALID_PERMISSIONS_FILE_ACCESS;
	}
	else if (pathToFileExists(absolutePath))
	{
		absolutePath = std::filesystem::absolute(absolutePath);
		if (canUserAccessFile(absolutePath, username))
			path = absolutePath;
		else
			status = Status::INVALID_PERMISSIONS_FILE_ACCESS;
	}
	else
		status = Status::NO_FILE_PATH_FOUND;

	if (std::filesystem::is_directory(path))
		status = Status::FILE_IS_DIRECTORY;

	if (status != Status::READY)
		return;

	lineOfOccurence = findLineNumber();
	if (lineOfOccurence == -1)
		status = Status::TEXT_NOT_FOUND;
}

int FindCommand::findLineNumber()
{
	std::ifstream fin(path);
	int isFound = -1;
	int patternLength = pattern.length();

	if (fin.is_open())
	{
		std::string line;
		int lineCounter = 1;

		while (isFound == -1 && std::getline(fin, line))
		{
			int lineLength = (int)line.length();
			for (int j = 0; j < lineLength && lineLength - j >= patternLength; ++j)
			{
				if (line.substr(j, patternLength) == pattern)
					isFound = lineCounter;
			}

			++lineCounter;
		}

		fin.close();
	}

	return isFound;
}

void FindCommand::decomposeArgumentList()
{
	path = argumentList[2];
	pattern = argumentList[1];
}

bool FindCommand::argumentListSizeCorrect()
{
	bool isGood = true;
	if (argumentList.size() < 3)
	{
		status = Status::TOO_FEW_ARGUMENTS;
		isGood = false;
	}
	else if (argumentList.size() > 3)
	{
		status = Status::TOO_MANY_ARGUMENTS;
		isGood = false;
	}

	return isGood;
}
