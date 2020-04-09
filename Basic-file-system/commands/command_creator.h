#pragma once

#include "abstract_command.h"
#include "where_command.h"

#include <vector>
#include <string>

//returns nullptr if the command name is not valid
AbstractCommand* createCommand(std::string&);