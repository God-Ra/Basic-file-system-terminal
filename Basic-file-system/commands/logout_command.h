#pragma once

#include "abstract_command.h"
#include "helper_functions.h"
#include "enums.h"

#include <iostream>
#include <vector>
#include <string>

class LogoutCommand : public AbstractCommand
{
public:
	LogoutCommand(const std::vector<std::string>& argumentList);

	virtual int execute(std::filesystem::path&, const std::string&);
private:
	const std::string COMMAND_NAME = "logout";
	std::vector<std::string> argumentList;

	Status status;

	void setCommandStatus(std::filesystem::path& , const std::string&);

	bool argumentListSizeCorrect();

	virtual ~LogoutCommand() {}
};