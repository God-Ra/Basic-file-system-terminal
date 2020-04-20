#pragma once

#pragma once

#include "abstract_command.h"
#include "enums.h"

#include <iostream>
#include <stdlib.h>

class ClsCommand : public AbstractCommand
{
public:
	ClsCommand(const std::vector<std::string>& argumentList);

	virtual int execute(std::filesystem::path&, const std::string&);
private:
	const std::string COMMAND_NAME = "cls";
	std::vector<std::string> argumentList;
	Status status;

	void setCommandStatus(std::filesystem::path&, const std::string&);

	bool argumentListSizeCorrect();

	virtual ~ClsCommand() {}
};