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

	virtual void execute(std::filesystem::path&);
private:
	const std::string COMMAND_NAME = "go";
	std::vector<std::string> argumentList;

	Status status;

	void setCommandStatus();
};