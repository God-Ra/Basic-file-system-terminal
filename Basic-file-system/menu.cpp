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

/*
==============
canUserEnterLocation

Function that checks whether the user is permitted to enter the location given by path
Returns 1 if the user has permission to enter the location, 0 otherwise
==============
*/
bool canUserEnterLocation(const std::filesystem::path& path, const std::string& username)
{
	std::string startingPath = "C:\\oosproject\\users\\" + username;
	std::string path_string = path.u8string();

	if (path_string.length() < startingPath.length())
		return 0;

	for (int i = 0; i < (int)startingPath.length(); ++i)
		if (startingPath[i] != path_string[i])
			return 0;

	return 1;
}

void changeSlashes(std::string& input)
{
	for (char& c : input)
	{
		if (c == '/')
			c = '\\';
	}
}

/*
changeLocation

TESTED
*/
void changeLocation(std::filesystem::path& currentLocation, std::string& input, const std::string& username)
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

	//This is done in case the input uses / for directories
	changeSlashes(input);

	std::filesystem::path nextLocation;
	if (input == "go ..")
		nextLocation = currentLocation.parent_path();
	else if (relative)
		nextLocation = currentLocation / input.substr(3, input.length() - 3);
	else if (absolute)
		nextLocation = input.substr(3, input.length() - 3);

	if (canUserEnterLocation(nextLocation, username))
		currentLocation = nextLocation;
	else
		std::cout << "You do not have permissions to enter the desired location!\n\n";
}

void listDirectories(const std::filesystem::path& currentLocation, std::string& input, const std::string& username)
{

}

/*
isCreatePathAndCommandCorrect

Takes currentLocation, inputstring and username
Returns 1 if the written command is valid and if the path specified is correct, otherwise returns 0
SIDE EFFECT: It strips input from the command parts, so only the part specifying the file path stayed
*/
bool isCreatePathAndCommandCorrect(const std::filesystem::path& currentLocation, std::string &input, const std::string& username)
{
	if (input.length() == 7)
	{
		std::cout << "The command is invalid!\n\n";
		return 0;
	}
	input = input.substr(7, input.length() - 7);

	std::filesystem::path newDataLocation;
	if (input.substr(0, 3) == "-d ")
	{
		if (input.length() <= 3)
		{
			std::cout << "The command is invalid!\n\n";
			return 0;
		}

		input = input.substr(3, input.length() - 3);
	}
	else if (input.substr(0, 2) == "-d" && input.length() == 2)
	{
		std::cout << "The command is invalid!\n\n";
		return 0;
	}

	newDataLocation = input;
	newDataLocation = newDataLocation.parent_path();

	bool absolute = checkPathExists(newDataLocation);
	bool relative = checkPathExists(currentLocation / newDataLocation);
	if (!absolute && !relative)
	{
		std::cout << "\nThe specified path does not exist!\n\n";
		return 0;
	}

	if (relative)
		newDataLocation = currentLocation / newDataLocation;
	else if (absolute)
		newDataLocation = newDataLocation;
	if (!canUserEnterLocation(newDataLocation, username))
	{
		std::cout << "You do not have permissions to enter the desired location!\n\n";
		return 0;
	}

	return 1;
}

std::filesystem::path setLocationToInput(const std::filesystem::path& currentLocation, const std::string& input)
{
	std::filesystem::path newDataLocation = input;
	newDataLocation = newDataLocation.parent_path();
	bool absolute = checkPathExists(newDataLocation);
	bool relative = checkPathExists(currentLocation / newDataLocation);
	if (relative)
		newDataLocation = currentLocation / newDataLocation;
	else if (absolute)
		newDataLocation = newDataLocation;

	return newDataLocation;
}

void createDirectory(const std::filesystem::path& currentLocation, std::string& input, const std::string& username)
{
	changeSlashes(input);

	//1-isDirectory; 0-isFile
	bool isDirectoryFile = false;
	if (input.length() > 7 && input.substr(7, 3) == "-d ")
		isDirectoryFile = true;
	if (!isCreatePathAndCommandCorrect(currentLocation, input, username))
		return;

	//This takes the last part of the user path that specifies the name of the directory/file to be created
	std::string fileName = "";
	for (int j = input.length() - 1; j >= 0 && input[j] != '\\'; --j)
		fileName += input[j];
	std::reverse(fileName.begin(), fileName.end());

	std::filesystem::path newDataLocation = setLocationToInput(currentLocation, input);
	
	bool isDirectoryCreated = false;
	try
	{
		if (!isDirectoryFile)
		{
			std::ofstream stream(newDataLocation / fileName);
			isDirectoryCreated = stream.is_open();
			stream.close();
		}
		else
			isDirectoryCreated = std::filesystem::create_directory(newDataLocation / fileName);
	}
	catch (const std::exception& ex)
	{
		std::cout << "There was an unexpected error creating a document!\n\n";
		return;
	}

	if (isDirectoryCreated && isDirectoryFile)
		std::cout << "The directory is created!\n\n";
	else if (isDirectoryCreated && !isDirectoryFile)
		std::cout << "The file is created!\n\n";
	else if (!isDirectoryCreated)
		std::cout << "There was an unexpected error creating a document!\n\n";
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
			changeLocation(currentLocation, input, username);
		}
		else if (input.substr(0, 7) == "create ")
		{
			createDirectory(currentLocation, input, username);
		}
		else if (input.substr(0, 5) == "list ")
		{
			listDirectories(currentLocation, input, username);
		}
	}
}