#pragma once

#pragma once

#include "abstract_command.h"
#include "helper_functions.h"
#include "enums.h"

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

class FindCommand : public AbstractCommand
{
public:
	FindCommand(const std::vector<std::string>& argumentList);

	virtual int execute(std::filesystem::path&, const std::string&);
private:
	const std::string COMMAND_NAME = "find";
	std::vector<std::string> argumentList;
	Status status;

	std::filesystem::path path;
	std::string pattern;
	int lineOfOccurence;

	void setCommandStatus(std::filesystem::path&, const std::string&);

	void printSuccessMessage();

	void printTextNotFoundMessage();

	int findLineNumber();

	void decomposeArgumentList();

	bool argumentListSizeCorrect();

	virtual ~FindCommand() {}
};