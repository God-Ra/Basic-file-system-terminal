#pragma once

#include "abstract_command.h"
#include "helper_functions.h"
#include "enums.h"

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

class ListCommand : public AbstractCommand
{
public:
	ListCommand(const std::vector<std::string>& argumentList);

	virtual void execute(std::filesystem::path&, const std::string&);
private:
	const std::string COMMAND_NAME = "list";
	std::vector<std::string> argumentList;
	Status status;

	std::filesystem::path path;

	void setCommandStatus(std::filesystem::path&, const std::string&);

	void printDirectoryTree();

	std::string extractFileName(const std::filesystem::path& fullPath);

	void setListPath(const std::filesystem::path&);

	bool argumentListSizeCorrect();

	virtual ~ListCommand() {}
};