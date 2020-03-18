#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include "gline.h"
#include "menu.h"

/*
==========
isUsernameValid

The function checks whether pair of (username, password) exist in folder "users.txt"
returns 1 if the pair exists, returns 0 otherwise
The function does not check whether the file "users.txt" is correctly written, takes it as a given
If the file does not exist the function still works
==========
*/
bool isUsernameValid(const std::string& username, const std::string& password);

int main()
{
	std::string username;
	while (1)
	{
		std::cout << ">>";
		std::string input;
		std::getline(std::cin, input);

		if (input == "login")
		{
			std::string password;
			getLine(username, 31, "Username: ");
			getLineAsterisks(password, 31, "Password: ");

			if (isUsernameValid(username, password))
			{
				std::cout << "\nWelcome, " << username << "!\n\n";
				mainMenu(username);
			}
			else
			{
				std::cout << "\nUsername or password are invalid!\n\n";
			}
		}
		else
		{
			std::cout << "You are not logged in! To login use command \"login\"\n\n";
		}
	}
}

bool isUsernameValid(const std::string& username, const std::string& password)
{
	std::ifstream fileUsers;
	fileUsers.open("users.txt", std::ios::in);

	bool isUserFound = false;
	std::string fileUsername = "", filePassword = "";
	while (fileUsers.good() && !isUserFound)
	{
		std::getline(fileUsers, fileUsername);
		std::getline(fileUsers, filePassword);

		if (fileUsername == username && filePassword == password)
			isUserFound = true;
	}

	fileUsers.close();
	return isUserFound;
}