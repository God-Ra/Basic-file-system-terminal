#include "menu.h"

void mainMenu(const std::string& username)
{
	std::string input;
	std::filesystem::path currentLocation = "C:\\oosproject\\users\\" + username;

	bool running = true;
	while (running)
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
			running = false;
	}
}