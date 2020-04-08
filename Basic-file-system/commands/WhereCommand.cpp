#include "WhereCommand.h"

void WhereCommand::execute(std::filesystem::path &currentLocation)
{
	printCurrentLocation(currentLocation);
}

void WhereCommand::printCurrentLocation(const std::filesystem::path &currentLocation)
{
	std::cout << "\nYour current location: " << currentLocation << "\n\n";
}