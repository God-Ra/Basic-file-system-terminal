#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>
#include "tests.h"
#include "constants.h"

void giveLocation(const std::filesystem::path& currentLocation);

bool checkPathExists(const std::filesystem::path& path);

/*
==============
canUserEnterLocation

Function that checks whether the user is permitted to enter the location given by path
Returns 1 if the user has permission to enter the location, 0 otherwise
==============
*/
bool canUserEnterLocation(const std::filesystem::path& path, const std::string& username);

void changeSlashes(std::string& input);

void changeLocation(std::filesystem::path& currentLocation, std::string& input, const std::string& username);

void listDirectories(const std::filesystem::path& currentLocation, std::string& input, const std::string& username);

/*
isCreatePathAndCommandCorrect

Takes currentLocation, inputstring and username
Returns 1 if the written command is valid and if the path specified is correct, otherwise returns 0
SIDE EFFECT: It strips input from the command parts, so only the part specifying the file path stayed
*/
bool isCreatePathAndCommandCorrect(const std::filesystem::path & currentLocation, std::string & input, const std::string & username);

void createDirectory(const std::filesystem::path & currentLocation, std::string & input, const std::string & username);

void mainMenu(const std::string& username);