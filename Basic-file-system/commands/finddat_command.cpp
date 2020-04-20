#include "finddat_command.h"

FindDatCommand::FindDatCommand(const std::vector<std::string>& argumentList)
{
	this->argumentList = argumentList;
}

int FindDatCommand::execute(std::filesystem::path& currentLocation, const std::string &username)
{
	setCommandStatus(currentLocation, username);

	switch (status)
	{
	case Status::READY:
		searchDirectory();
		std::cout << "Total number of matches: " << matches << "\n";
		break;
	case Status::TOO_MANY_ARGUMENTS:
		std::cout << "Command: \"" << COMMAND_NAME << "\", ERROR: There are too many arguments!\n";
		break;
	case Status::TOO_FEW_ARGUMENTS:
		std::cout << "Command: \"" << COMMAND_NAME << "\", ERROR: There are not enough arguments!\n";
		break;
	case Status::INVALID_PERMISSIONS_DIRECTORY_SEARCH:
		std::cout << "Command: \"" << COMMAND_NAME << "\", ERROR: You do not have permissions to search the documents from this location!\n";
		break;
	case Status::NO_DIRECTORY_PATH_FOUND:
		std::cout << "Command: \"" << COMMAND_NAME << "\", ERROR: The specified directory is not found!\n";
		break;
	}

	return 0;
}

void FindDatCommand::setCommandStatus(std::filesystem::path& currentLocation, const std::string& username)
{
	status = Status::READY;
	if (!argumentListSizeCorrect())
		return;
	setPath(currentLocation);
	setFileName();

	std::filesystem::path relativePath = currentLocation / path;
	std::filesystem::path absolutePath = path;

	if (pathToDirectoryExists(relativePath))
	{
		relativePath = std::filesystem::absolute(relativePath);
		if (canUserEnterDirectory(relativePath, username))
			path = relativePath;
		else
			status = Status::INVALID_PERMISSIONS_DIRECTORY_SEARCH;
	}
	else if (pathToDirectoryExists(absolutePath))
	{
		absolutePath = std::filesystem::absolute(absolutePath);
		if (canUserEnterDirectory(absolutePath, username))
			path = absolutePath;
		else
			status = Status::INVALID_PERMISSIONS_DIRECTORY_SEARCH;
	}
	else
		status = Status::NO_DIRECTORY_PATH_FOUND;

	return;
}

void FindDatCommand::searchDirectory()
{
	for (auto i = std::filesystem::recursive_directory_iterator(path);
		i != std::filesystem::recursive_directory_iterator();
		++i)
	{
		if (extractFileName((*i).path()) == fileName)
		{
			std::cout << (*i).path() << "\n";
			++matches;
		}
	}
}

std::string FindDatCommand::extractFileName(const std::filesystem::path& fullPath)
{
	std::string path_string = fullPath.u8string();
	std::string ans = "";
	for (int j = path_string.length() - 1; j >= 0 && path_string[j] != '\\'; --j)
		ans += path_string[j];
	std::reverse(ans.begin(), ans.end());

	return ans;
}

void FindDatCommand::setFileName()
{
	fileName = argumentList[1];
}

void FindDatCommand::setPath(const std::filesystem::path &currentLocation)
{
	if (argumentList.size() == 2)
		path = currentLocation;
	else
		path = argumentList[2];
}

bool FindDatCommand::argumentListSizeCorrect()
{
	bool isGood = true;
	if (argumentList.size() < 2)
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
