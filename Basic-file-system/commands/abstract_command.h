#pragma once

#include <filesystem>

class AbstractCommand
{
public:
	virtual int execute(std::filesystem::path&, const std::string&) = 0;

	virtual ~AbstractCommand() {}
};