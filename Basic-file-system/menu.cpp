#include "menu.h"

void mainMenu(const std::string& username)
{
	std::string input;
	std::filesystem::path currentLocation = "C:\\oosproject\\users\\" + username;

	if (!std::filesystem::exists(currentLocation))
	{
		bool directoriesCreated = std::filesystem::create_directories(currentLocation);
		if (!directoriesCreated)
		{
			std::cout << "There was an error with setting up the filesystem!\n\n";
			return;
		}
	}

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