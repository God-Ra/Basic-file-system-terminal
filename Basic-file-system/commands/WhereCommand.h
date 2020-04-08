#pragma once

#include "Command.h"

#include <iostream>

class WhereCommand : public Command
{
public:
	WhereCommand()
	{

	}

	virtual void execute(std::filesystem::path&);
private:
	void printCurrentLocation(const std::filesystem::path&);
};