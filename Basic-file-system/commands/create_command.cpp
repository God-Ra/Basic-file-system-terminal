#include "create_command.h"

CreateCommand::CreateCommand(const std::vector<std::string>& argumentList)
{
	this->argumentList = argumentList;
}

void CreateCommand::execute(std::filesystem::path& currentLocation, const std::string& username)
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
	case Status::PATH_MISSING:
		std::cout << "Command: \"" << COMMAND_NAME << "\", ERROR: You need to provide a path!\n";
		break;
	case Status::INVALID_PERMISSIONS_DIRECTORY_CREATE:
		std::cout << "Command: \"" << COMMAND_NAME << "\", ERROR: You do not have permissions to create a document in this location!\n";
		break;
	case Status::NO_DIRECTORY_PATH_FOUND:
		std::cout << "Command: \"" << COMMAND_NAME << "\", ERROR: The specified directory is not found!\n";
		break;
	case Status::CREATION_FAILED:
		std::cout << "Command: \"" << COMMAND_NAME << "\", ERROR: Document/Directory creation failed!\n";
		break;
	}
}

void CreateCommand::setCommandStatus(std::filesystem::path& currentLocation, const std::string& username)
{
	status = Status::READY;
	if (!argumentListSizeCorrect())
		return;
	if (!argumentListValid())
		return;
	decomposeArgumentList();
	decomposePath();


	std::filesystem::path relativePath = currentLocation / creationDirectory;
	std::filesystem::path absolutePath = creationDirectory;

	if (pathToDirectoryExists(relativePath))
	{
		relativePath = std::filesystem::absolute(relativePath);
		if (canUserEnterDirectory(relativePath, username))
			creationDirectory = relativePath;
		else
			status = Status::INVALID_PERMISSIONS_DIRECTORY_CREATE;
	}
	else if (pathToDirectoryExists(absolutePath))
	{
		absolutePath = std::filesystem::absolute(absolutePath);
		if (canUserEnterDirectory(absolutePath, username))
			creationDirectory = absolutePath;
		else
			status = Status::INVALID_PERMISSIONS_DIRECTORY_CREATE;
	}
	else
		status = Status::NO_DIRECTORY_PATH_FOUND;

	if (status == Status::READY)
		createFile();

	return;
}

void CreateCommand::createFile()
{
	bool isCreationSuccessful = false;
	try
	{
		if (!isDirectory)
		{
			std::ofstream stream(creationDirectory / fileName);
			isCreationSuccessful = stream.is_open();
			stream.close();
		}
		else
			isCreationSuccessful = std::filesystem::create_directory(creationDirectory / fileName);
	}
	catch (const std::exception&)
	{
		status = Status::CREATION_FAILED;
		return;
	}

	if (!isCreationSuccessful)
		status = Status::CREATION_FAILED;
}

void CreateCommand::decomposePath()
{
	creationDirectory = fullPath.parent_path();
	fileName = extractFileName();
}

std::string CreateCommand::extractFileName()
{
	std::string path_string = fullPath.u8string();
	std::string ans = "";
	for (int j = path_string.length() - 1; j >= 0 && path_string[j] != '\\'; --j)
		ans += path_string[j];
	std::reverse(ans.begin(), ans.end());

	return ans;
}

void CreateCommand::decomposeArgumentList()
{
	if (argumentList[1] == "-d")
	{
		isDirectory = true;
		fullPath = argumentList[2];
	}
	else 
		fullPath = argumentList[1];
}

bool CreateCommand::argumentListSizeCorrect()
{
	bool isGood = true;
	if (argumentList.size() < 1)
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

bool CreateCommand::argumentListValid()
{
	bool isGood = true;
	if ((argumentList.size() == 1) || (argumentList.size() == 2  && argumentList[1] == "-d"))
	{
		status = Status::PATH_MISSING;
		isGood = false;
	}

	return isGood;
}

void CreateCommand::printSuccessMessage()
{
	std::cout << "Command: \"" << COMMAND_NAME << "\", successfully created a ";
	if (isDirectory)
		std::cout << "directory";
	else
		std::cout << "file";
	std::cout << "\nPATH: \"" << creationDirectory / fileName << "\"\n";
}