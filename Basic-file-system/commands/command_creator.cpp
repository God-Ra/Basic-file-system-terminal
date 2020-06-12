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
		std::cout << "ERROR: Every start of quotation marks should have an end\n";
		return nullptr;
	}

	if (argumentList.size() == 0)
		return nullptr;

	std::string commandName = argumentList[0];

	if (commandName == "where")
		return new WhereCommand(argumentList);
	else if (commandName == "go")
		return new GoCommand(argumentList);
	else if (commandName == "create")
		return new CreateCommand(argumentList);
	else if (commandName == "list")
		return new ListCommand(argumentList);
	else if (commandName == "print")
		return new PrintCommand(argumentList);
	else if (commandName == "find")
		return new FindCommand(argumentList);
	else if (commandName == "findDat")
		return new FindDatCommand(argumentList);
	else if (commandName == "cls")
		return new ClsCommand(argumentList);
	else if (commandName == "logout")
		return new LogoutCommand(argumentList);
	else
	{
		std::cout << "ERROR: The command \"" << commandName << "\" is not found\n";
		return nullptr;
	}
}