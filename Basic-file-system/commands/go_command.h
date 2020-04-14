#pragma once

#include "abstract_command.h"
#include "helper_functions.h"
#include "enums.h"

#include <iostream>
#include <vector>
#include <string>

class GoCommand : public AbstractCommand
{
public:
	GoCommand(const std::vector<std::string>& argumentList);

	virtual void execute(std::filesystem::path&, const std::string&);
private:
	const std::string COMMAND_NAME = "go";
	std::vector<std::string> argumentList;

	std::filesystem::path newLocation;

	Status status;

	void setCommandStatus(std::filesystem::path&, const std::string&);

	bool argumentListSizeCorrect();

	virtual ~GoCommand() {}
};