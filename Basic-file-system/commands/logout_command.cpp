#include "logout_command.h"

LogoutCommand::LogoutCommand(const std::vector<std::string>& argumentList)
{
	this->argumentList = argumentList;
}

int LogoutCommand::execute(std::filesystem::path& currentLocation, const std::string& username)
{
	setCommandStatus(currentLocation, username);

	switch (status)
	{
	case Status::READY:
		return 1;
		break;
	case Status::TOO_MANY_ARGUMENTS:
		std::cout << "Command: \"" << COMMAND_NAME << "\", ERROR: There are too many arguments\n";
		break;
	}

	return 0;
}

void LogoutCommand::setCommandStatus(std::filesystem::path& currentLocation, const std::string& username)
{
	status = Status::READY;
	if (!argumentListSizeCorrect())
		return;
}

bool LogoutCommand::argumentListSizeCorrect()
{
	bool isGood = true;
	if (argumentList.size() > 1)
	{
		status = Status::TOO_MANY_ARGUMENTS;
		isGood = false;
	}

	return isGood;
}
