#include "command_creator.h"

AbstractCommand* createCommand(std::string &inputString)
{
	std::vector<std::string> argumentList;
	try
	{
		parseInputLine(argumentList, inputString);
	}
	catch (const std::exception&)
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
	else if (argumentList[0] == "create")
		return new CreateCommand(argumentList);
	else if (argumentList[0] == "list")
		return new ListCommand(argumentList);
	else if (argumentList[0] == "print")
		return new PrintCommand(argumentList);
	else if (argumentList[0] == "find")
		return new FindCommand(argumentList);
	else if (argumentList[0] == "findDat")
		return new FindDatCommand(argumentList);
	else if (argumentList[0] == "cls")
		return new ClsCommand(argumentList);
	else if (argumentList[0] == "logout")
		return new LogoutCommand(argumentList);
	else
	{
		std::cout << "ERROR: The command \"" << argumentList[0] << "\" is not found\n";
		return nullptr;
	}
}