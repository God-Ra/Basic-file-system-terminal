#pragma once

#include <vector>
#include <string>
#include <filesystem>

//Throws std::exception if there is not an even number of quotation marks
//Overwrites any data in vector of strings
void parseInputLine(std::vector<std::string>&, const std::string&) noexcept(false); 

//Changes slashes from right pointing to left pointing
void changeSlashes(std::string& input);

bool pathToDirectoryExists(const std::filesystem::path&);

bool pathToFileExists(const std::filesystem::path & path);

bool canUserAccessFile(const std::filesystem::path & path, const std::string & username);

bool canUserEnterDirectory(const std::filesystem::path& path, const std::string& username);