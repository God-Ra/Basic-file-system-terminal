#include "where_command.h"

WhereCommand::WhereCommand(const std::vector<std::string>& argumentList)
{
	this->argumentList = argumentList;
	setCommandStatus();
}

void WhereCommand::execute(std::filesystem::path &currentLocation)
{
	printCurrentLocation(currentLocation);
}

void WhereCommand::setCommandStatus()
{
	//This shouldn't happen
	if (argumentList[0] != COMMAND_NAME)
		status = Status::COMMAND_NAME_FAILURE;

	if (argumentList.size() > 1)
		status = Status::TOO_MANY_ARGUMENTS;
}

void WhereCommand::printCurrentLocation(const std::filesystem::path &currentLocation)
{
	std::cout << "\nYour current location: " << currentLocation << "\n\n";
}