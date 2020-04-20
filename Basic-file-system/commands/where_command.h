#pragma once

#include "abstract_command.h"
#include "helper_functions.h"
#include "enums.h"

#include <iostream>
#include <vector>
#include <string>

class WhereCommand : public AbstractCommand
{
public:
	WhereCommand(const std::vector<std::string>& argumentList);

	virtual int execute(std::filesystem::path&, const std::string&);
private:
	const std::string COMMAND_NAME = "where";
	std::vector<std::string> argumentList;

	Status status;

	void setCommandStatus();
	
	void printCurrentLocation(const std::filesystem::path&);

	virtual ~WhereCommand() {}
};