#pragma once

#include "abstract_command.h"
#include "helper_functions.h"
#include "enums.h"

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

//If there is a directory with the same name, then the creation will fail
//It a file is being created and there is one with the same name it will overwrite it
class CreateCommand : public AbstractCommand
{
public:
	CreateCommand(const std::vector<std::string>& argumentList);

	virtual int execute(std::filesystem::path&, const std::string&);
private:
	const std::string COMMAND_NAME = "create";
	std::vector<std::string> argumentList;
	Status status;

	bool isDirectory = false;
	std::filesystem::path fullPath;

	std::filesystem::path creationDirectory;
	std::string fileName;

	void setCommandStatus(std::filesystem::path&, const std::string&);

	void createFile();

	void decomposePath();

	std::string extractFileName();

	void decomposeArgumentList();

	bool argumentListSizeCorrect();

	bool argumentListValid();

	void printSuccessMessage();

	virtual ~CreateCommand() {}
};