#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include "gline.h"
#include "menu.h"

/*
==========
isUsernameValid

The function returns true if a pair (username, password) exists in 
file "users.txt", returns false otherwise
==========
*/
bool isUsernameValid(const std::string& username, const std::string& password);

int main()
{
	std::string username;
	bool running = true;
	while (running)
	{
		std::cout << ">>";
		std::string input;
		std::getline(std::cin, input);

		if (input == "login")
		{
			std::string password;
			getLine(username, USERNAME_LENGTH, "Username: ");
			getLineAsterisks(password, PASSWORD_LENGTH, "Password: ");

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
		else if (input == "exit")
		{
			running = false;
		}
		else
		{
			std::cout << "You are not logged in! Use command \"login\"\n\n";
		}
	}
}

bool isUsernameValid(const std::string& username, const std::string& password)
{
	std::ifstream fileUsers;
	fileUsers.open("users.txt", std::ios::in);

	if (!fileUsers.is_open())
	{
		std::cout << "The file where users are stored could not be opened!";
		return false;
	}

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