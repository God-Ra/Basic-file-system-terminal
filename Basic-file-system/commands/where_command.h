#pragma once

#include "abstract_command.h"
#include "helper_functions.h"

#include <iostream>
#include <vector>
#include <string>

enum class Status
{
	READY,
	TOO_MANY_ARGUMENTS,
	COMMAND_NAME_FAILURE
};

class WhereCommand : public AbstractCommand
{
public:
	WhereCommand(const std::vector<std::string>& argumentList);

	virtual void execute(std::filesystem::path&);
private:
	const std::string COMMAND_NAME = "where";
	std::vector<std::string> argumentList;

	Status status;

	void setCommandStatus();

	void printCurrentLocation(const std::filesystem::path&);
};