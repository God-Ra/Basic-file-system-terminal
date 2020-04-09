#include "command_creator.h"

AbstractCommand* createCommand(std::string &inputString)
{
	std::vector<std::string> argumentList;
	splitStringIntoWords(argumentList, inputString);
	if (argumentList[0] == "where")
		return new WhereCommand(argumentList);
}

//THINK ABOUT IF YOU WANT TO GIVE THE FILESYSTEM PATH WHILE CREATING THE OBJECT IMMEDIATELY