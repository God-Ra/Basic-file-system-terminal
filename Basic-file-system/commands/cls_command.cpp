#include "cls_command.h"

ClsCommand::ClsCommand(const std::vector<std::string>& argumentList)
{
	this->argumentList = argumentList;
}

void ClsCommand::execute(std::filesystem::path& currentLocation, const std::string &username)
{
	setCommandStatus(currentLocation, username);

	switch (status)
	{
	case Status::READY:
		system("CLS");
		break;
	case Status::TOO_MANY_ARGUMENTS:
		std::cout << "Command: \"" << COMMAND_NAME << "\", ERROR: There are too many arguments\n";
		break;
	}
}

void ClsCommand::setCommandStatus(std::filesystem::path& currentLocation, const std::string &username)
{
	status = Status::READY;
	if (!argumentListSizeCorrect())
		return;
}

bool ClsCommand::argumentListSizeCorrect()
{
	bool isGood = true;
	if (argumentList.size() > 1)
	{
		status = Status::TOO_MANY_ARGUMENTS;
		isGood = false;
	}

	return isGood;
}
