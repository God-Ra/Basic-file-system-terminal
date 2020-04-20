#include "go_command.h"

GoCommand::GoCommand(const std::vector<std::string>& argumentList)
{
	this->argumentList = argumentList;
}

int GoCommand::execute(std::filesystem::path& currentLocation, const std::string& currentUsername)
{
	setCommandStatus(currentLocation, currentUsername);

	switch (status)
	{
	case Status::READY:
		currentLocation = newLocation;
		break;
	case Status::TOO_MANY_ARGUMENTS:
		std::cout << "Command: \"" << COMMAND_NAME << "\", ERROR: There are too many arguments!\n";
		break;
	case Status::INVALID_PERMISSIONS_DIRECTORY_MOVE:
		std::cout << "Command: \"" << COMMAND_NAME << "\", ERROR: You do not have permissions to enter this location!\n";
		break;
	case Status::NO_DIRECTORY_PATH_FOUND:
		std::cout << "Command: \"" << COMMAND_NAME << "\", ERROR: The specified directory is not found!\n";
		break;
	case Status::TOO_FEW_ARGUMENTS:
		std::cout << "Command: \"" << COMMAND_NAME << "\", ERROR: There are not enough arguments!\n";
		break;
	}

	return 0;
}

void GoCommand::setCommandStatus(std::filesystem::path& currentLocation, const std::string& currentUsername)
{
	if (!argumentListSizeCorrect())
		return;
	changeSlashes(argumentList[1]);

	std::filesystem::path relativePath = currentLocation / argumentList[1];
	std::filesystem::path absolutePath = argumentList[1];

	status = Status::READY;
	if (pathToDirectoryExists(relativePath))
	{
		relativePath = std::filesystem::absolute(relativePath);
		if (canUserEnterDirectory(relativePath, currentUsername))
			newLocation = relativePath;
		else
			status = Status::INVALID_PERMISSIONS_DIRECTORY_MOVE;
	}
	else if (pathToDirectoryExists(absolutePath))
	{
		absolutePath = std::filesystem::absolute(absolutePath);
		if (canUserEnterDirectory(absolutePath, currentUsername))
			newLocation = absolutePath;
		else
			status = Status::INVALID_PERMISSIONS_DIRECTORY_MOVE;
	}
	else
		status = Status::NO_DIRECTORY_PATH_FOUND;
}

bool GoCommand::argumentListSizeCorrect()
{
	if (argumentList.size() > 2)
	{
		status = Status::TOO_MANY_ARGUMENTS;
		return 0;
	}
	else if (argumentList.size() == 1)
	{
		status = Status::TOO_FEW_ARGUMENTS;
		return 0;
	}
	return 1;
}