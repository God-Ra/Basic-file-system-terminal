#include "command_creator.h"

AbstractCommand* createCommand(std::string &inputString)
{
	std::vector<std::string> argumentList;
	try
	{
		parseInputLine(argumentList, inputString);
	}
	catch (const std::exception &ex)
	{
		std::cout << "ERROR: Each start of quotation marks should have an ending\n";
		return nullptr;
	}

	if (argumentList.size() == 0)
		return nullptr;

	if (argumentList[0] == "where")
		return new WhereCommand(argumentList);
	else if (argumentList[0] == "go")
		return new GoCommand(argumentList);
	else
	{
		std::cout << "ERROR: The command \"" << argumentList[0] << "\" is not found\n";
		return nullptr;
	}
}