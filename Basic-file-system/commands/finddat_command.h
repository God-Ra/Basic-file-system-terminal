#pragma once

#include "abstract_command.h"
#include "helper_functions.h"
#include "enums.h"

#include <iostream>
#include <vector>
#include <string>

//OVA KOMANDA DRUGACIJA NEGO KAKO PISE U PROJEKTNOM
class FindDatCommand : public AbstractCommand
{
public:
	FindDatCommand(const std::vector<std::string>& argumentList);

	virtual void execute(std::filesystem::path&, const std::string&);
private:
	const std::string COMMAND_NAME = "findDat";
	std::vector<std::string> argumentList;
	Status status;

	std::filesystem::path path;
	std::string fileName;
	int matches = 0;

	void setCommandStatus(std::filesystem::path&, const std::string&);

	void searchDirectory();

	std::string extractFileName(const std::filesystem::path& fullPath);

	void setFileName();

	void setPath(const std::filesystem::path&);

	bool argumentListSizeCorrect();

	virtual ~FindDatCommand() {}
};