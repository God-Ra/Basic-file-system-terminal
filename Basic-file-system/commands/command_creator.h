#pragma once

#include "abstract_command.h"
#include "where_command.h"
#include "go_command.h"
#include "create_command.h"
#include "list_command.h"
#include "print_command.h"
#include "find_command.h"
//reserved for finddat
#include "cls_command.h"

#include <vector>
#include <string>

//returns nullptr if the command name is not valid
AbstractCommand* createCommand(std::string&);