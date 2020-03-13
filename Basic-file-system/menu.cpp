#include "menu.h"

void giveLocation(const std::filesystem::path& currentLocation)
{
	std::cout << "\nYour current location: " << currentLocation << "\n\n";
}

bool checkPathExists(const std::filesystem::path& path)
{
	std::string path_string = path.u8string();

	for (char c : path_string)
	{
		//With this check there should be no exceptions that occurred in one of the tests
		if (c == '<' || c == '>' || c == '"' || c == '|' || c == '?' || c == '*')
			return 0;
	}

	//This is made to prevent exceptions
	bool res;
	try
	{
		res = std::filesystem::exists(path);
	}
	catch (...)
	{
		return 0;
	}

	return res;
}

void changeLocation(std::filesystem::path& currentLocation, std::string& input)
{
	bool absolute = checkPathExists(input.substr(3, input.length() - 3));
	bool relative = checkPathExists(currentLocation / input.substr(3, input.length() - 3));
	if (!absolute && !relative)
	{
		std::cout << "\nThe specified path does not exist!\n\n";
		return;
	}

	bool hasDots = false;
	for (char c : input)
		if (c == '.')
			hasDots = true;

	if (hasDots && input != "go ..")
	{
		std::cout << "\nUsage of dots is not allowed!\n\n";
		return;
	}
	else if (input == "go ..")
	{
		currentLocation = currentLocation.parent_path();
		return;
	}

	//This is done in case the input uses / for directories
	for (char& c : input)
	{
		if (c == '/')
			c = '\\';
	}

	if (relative)
		currentLocation = currentLocation / input.substr(3, input.length() - 3);
	else if (absolute)
		currentLocation = input.substr(3, input.length() - 3);
}

void mainMenu(const std::string& username)
{
	std::string input;
	std::filesystem::path currentLocation = "C:\\oosproject\\users\\" + username;

	/*for (const auto& dirEntry : std::filesystem::recursive_directory_iterator(currentLocation))
		std::cout << dirEntry.path() << "\n";
	std::filesystem::create_directory(currentLocation / "directory");*/
	pathExistsTests();

	while (1)
	{
		std::cout << username << ">>";
		std::getline(std::cin, input);

		if (input == "where")
		{
			giveLocation(currentLocation);
		}
		else if (input.substr(0, 3) == "go ")
		{
			changeLocation(currentLocation, input);
		}
	}
}