#include "print_command.h"

PrintCommand::PrintCommand(const std::vector<std::string>& argumentList)
{
	this->argumentList = argumentList;
}

int PrintCommand::execute(std::filesystem::path& currentLocation, const std::string& username)
{
	setCommandStatus(currentLocation, username);

	switch (status)
	{
	case Status::READY:
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
	case Status::FILE_OPEN_FAILURE:
		std::cout << "Command: \"" << COMMAND_NAME << "\", ERROR: The specified file could not be opened\n";
		break;
	case Status::NOT_TEXT_FILE:
		std::cout << "Command: \"" << COMMAND_NAME << "\", ERROR: The specified file is not a text file\n";
		break;
	}

	return 0;
}

void PrintCommand::setCommandStatus(std::filesystem::path& currentLocation, const std::string& username)
{
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

	if (status != Status::READY)
		return;

	if (!isTextFile())
		return;

	printData();
}

void PrintCommand::printData()
{
	std::ifstream fin(path);

	if (fin.is_open())
	{
		std::string line;
		while (std::getline(fin, line))
			std::cout << line << "\n";

		fin.close();
	}
	else
		status = Status::FILE_OPEN_FAILURE;
}

bool PrintCommand::isTextFile()
{
	if (path.extension().string() == ".txt")
		return 1;
	else
	{
		status = Status::NOT_TEXT_FILE;
		return 0;
	}
}

void PrintCommand::decomposeArgumentList()
{
	path = argumentList[1];
}

bool PrintCommand::argumentListSizeCorrect()
{
	bool isGood = true;
	if (argumentList.size() < 2)
	{
		status = Status::TOO_FEW_ARGUMENTS;
		isGood = false;
	}
	else if (argumentList.size() > 2)
	{
		status = Status::TOO_MANY_ARGUMENTS;
		isGood = false;
	}

	return isGood;
}
