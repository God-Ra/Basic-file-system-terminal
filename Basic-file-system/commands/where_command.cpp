#include "where_command.h"

WhereCommand::WhereCommand(const std::vector<std::string>& argumentList)
{
	this->argumentList = argumentList;
}

int WhereCommand::execute(std::filesystem::path &currentLocation, const std::string& username)
{
	setCommandStatus();

	switch (status)
	{
	case Status::READY:
		printCurrentLocation(currentLocation);
		break;
	case Status::TOO_MANY_ARGUMENTS:
		std::cout << "Command: \"" << COMMAND_NAME << "\", ERROR: There are too many arguments\n";
		break;
	}

	return 0;
}

void WhereCommand::setCommandStatus()
{
	if (argumentList.size() > 1)
		status = Status::TOO_MANY_ARGUMENTS;
	else
		status = Status::READY;
}

void WhereCommand::printCurrentLocation(const std::filesystem::path &currentLocation)
{
	std::cout << "Your current location: " << currentLocation << "\n";
}