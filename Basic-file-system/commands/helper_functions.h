#pragma once

#include <vector>
#include <string>

//Appends the split words at the end of the vector
//Old function that did not include quotation marks
void splitStringIntoWords(std::vector<std::string>&, std::string);

//Throws std::exception if there is not an even number of quotation marks
//Overwrites any data in the string
void parseInputLine(std::vector<std::string>&, const std::string&) noexcept(false); 