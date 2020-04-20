#include "menu.h"

void mainMenu(const std::string& username)
{
	std::string input;
	std::filesystem::path currentLocation = "C:\\oosproject\\users\\" + username;

	/*while (1)
	{
		std::cout << username << ">>";
		std::getline(std::cin, input);

		if (input == "where")
		{
			printLocation(currentLocation);
		}
		else if (input == "go" || input.substr(0, 3) == "go ")
		{
			if (input != "go")
				changeLocation(currentLocation, input, username);
			else
			{
				std::cout << "Changes the current location of the user\n\ngo [PATH]\n\nPATH can be relative or absolute\n\n";
			}
		}
		else if (input == "create" || input.substr(0, 7) == "create ")
		{
			if (input != "create")
				createDirectory(currentLocation, input, username);
			else
			{
				std::cout << "Creates a file or a document\n\n"
					<< "create [-d] [PATH]\n\n"
					<< "-d specifies that you want to create a directory\n"
					<< "PATH can be relative or absolute path\n"
					<< "PATH\\.. must exist, the folder in which the file/directory is created must exist\n\n";
			}
		}
		else if (input.substr(0, 4) == "list")
		{
			listDirectories(currentLocation, input, username);
		}
		else if (input == "print" || input.substr(0, 6) == "print ")
		{
			if (input != "print")
				printText(currentLocation, input, username);
			else
			{
				std::cout << "Prints data from a text document\n\n"
					<< "print PATH\n\n"
					<< "PATH can be relative or absolute path\n"
					<< "PATH must lead to a .txt document\n\n"
					;
			}
		}
		else if (input == "find" || input.substr(0, 5) == "find ")
		{
			if (input != "find")
				findText(currentLocation, input, username);
			else
			{
				std::cout << "Prints the line of the first occurrence of the text in a .txt document\n\n"
					<< "find \"text\" PATH\n\n"
					<< "PATH can be relative or absolute path\n"
					<< "PATH must lead to a .txt document\n"
					<< "text must have at least one character\n\n"
					;
			}
		}
		else if (input == "findDat" || input.substr(0, 7) == "findDat")
		{
			if (input != "findDat")
				findFile(currentLocation, input, username);
			else
			{
				std::cout << "Searches for all occurrences of a file in a directory\n\n"
					<< "findDat FILENAME PATH\n\n"
					<< "PATH can be relative or absolute path\n"
					<< "PATH must lead to a directory\n\n"
					;
			}
		}
		else if (input == "logout")
			return;
		else
			std::cout << "The command is not recognizable!\n\n";
	}*/

	while (1)
	{
		std::cout << username << ">>";
		std::getline(std::cin, input);

		AbstractCommand *command = createCommand(input);
		int returnFromMain = 0;

		if (command != nullptr)
			returnFromMain = command->execute(currentLocation, username);
		
		std::cout << "\n";

		delete command;

		if (returnFromMain)
			return;
	}
}