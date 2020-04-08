#pragma once

#include <filesystem>

class Command
{
public:
	virtual void execute(std::filesystem::path&) = 0;
};