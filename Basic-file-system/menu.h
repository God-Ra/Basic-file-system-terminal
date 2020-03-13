#pragma once

#include <string>
#include <iostream>
#include <filesystem>
#include <vector>
#include "tests.h"

void giveLocation(const std::filesystem::path& currentLocation);

bool checkPathExists(const std::filesystem::path& path);

void mainMenu(const std::string& username);