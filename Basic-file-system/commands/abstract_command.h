#pragma once

#include <filesystem>

class AbstractCommand
{
public:
	virtual void execute(std::filesystem::path&) = 0;
};