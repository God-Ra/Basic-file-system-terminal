#pragma once

#include "abstract_command.h"
#include "helper_functions.h"
#include "enums.h"

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

class PrintCommand : public AbstractCommand
{
public:
	PrintCommand(const std::vector<std::string>& argumentList);

	virtual void execute(std::filesystem::path&, const std::string&);
private:
	const std::string COMMAND_NAME = "print";
	std::vector<std::string> argumentList;
	Status status;

	std::filesystem::path path;

	void setCommandStatus(std::filesystem::path&, const std::string&);

	void printData();

	bool isTextFile();

	void decomposeArgumentList();

	bool argumentListSizeCorrect();

	virtual ~PrintCommand() {}
};