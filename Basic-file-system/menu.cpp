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

		//The if part is made to combat the paths which have only empty characters or only dots
		//with empty characters, the system would return that there exists such path when it does not
		//so I just try to iterate over that path that should be a directory and if I get an exception
		//the path does not exist
		if (std::filesystem::is_directory(path))
			auto i = std::filesystem::recursive_directory_iterator(path);
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

	if (canUserEnterLocation(nextLocation, username) && std::filesystem::is_directory(nextLocation))
		currentLocation = nextLocation;
	else if (!std::filesystem::is_directory(nextLocation))
		std::cout << "The path does not lead to a directory!\n\n";
	else
		std::cout << "You do not have permissions to enter the desired location!\n\n";
}

/*
isPathCorrect

path - path to check
Given path returns 1 if the relative or the absolute path is correct and if the user has valid
permissions to enter the location specified by path, otherwise returns 1
*/
bool isPathCorrect(const std::filesystem::path& path, const std::filesystem::path& currentLocation, const std::string& username)
{
	bool absolute = checkPathExists(path);
	bool relative = checkPathExists(currentLocation / path);
	if (!absolute && !relative)
	{
		std::cout << "\nThe specified path does not exist!\n\n";
		return 0;
	}

	std::filesystem::path currentPath = path;
	if (relative)
		currentPath = currentLocation / currentPath;
	else if (absolute)
		currentPath = currentPath;
	if (!canUserEnterLocation(currentPath, username))
	{
		std::cout << "You do not have permissions to enter the desired location!\n\n";
		return 0;
	}

	return 1;
}

std::string getEndDirectory(const std::filesystem::path& path)
{
	std::string path_string = path.u8string();
	std::string ans = "";
	for (int j = path_string.length() - 1; j >= 0 && path_string[j] != '\\'; --j)
		ans += path_string[j];
	std::reverse(ans.begin(), ans.end());

	return ans;
}

void listDirectories(const std::filesystem::path& currentLocation, std::string& input, const std::string& username)
{
	std::filesystem::path pathPrint;
	if (input == "list" || input == "list ")
		pathPrint = currentLocation;
	else
	{
		input = input.substr(5, input.length() - 5);
		pathPrint = input;

		if (!isPathCorrect(pathPrint, currentLocation, username))
			return;
		if (checkPathExists(currentLocation / pathPrint))
		{
			if (std::filesystem::is_directory(currentLocation / pathPrint))
			{
				pathPrint = currentLocation / pathPrint;
			}
			else
			{
				std::cout << "The path is not a directory!\n\n";
				return;
			}
		}
		else if (checkPathExists(pathPrint))
		{
			//Check if the path is directory, if it's not you don't have something to iterate on
			if (std::filesystem::is_directory(pathPrint))
				pathPrint = pathPrint;
			else
			{
				std::cout << "The path is not a directory!\n\n";
				return;
			}
		}
	}

	std::cout << "\n";
	for (auto i = std::filesystem::recursive_directory_iterator(pathPrint);
		i != std::filesystem::recursive_directory_iterator();
		++i)
	{
		std::cout << std::string(i.depth(), '\t') << 
			"\"" << getEndDirectory((*i).path()) << "\"" << "\n";
	}

	std::cout << "\n";
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

	return isPathCorrect(newDataLocation, currentLocation, username);
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
	std::string fileName = getEndDirectory(input);
//	for (int j = input.length() - 1; j >= 0 && input[j] != '\\'; --j)
//		fileName += input[j];
//	std::reverse(fileName.begin(), fileName.end());

	std::filesystem::path newDataLocation = setLocationToInput(currentLocation, input);
	
	bool isDirectoryCreated = false;
	try
	{
		std::cout << "Place: " << newDataLocation / fileName << "\n";
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

void printDataFromTextFile(const std::filesystem::path& pathPrint)
{
	std::ifstream fin(pathPrint);

	if (fin.is_open())
	{
		std::string line;
		while (std::getline(fin, line))
			std::cout << line << "\n";

		fin.close();
	}
	else
		std::cout << "Unable to open the text file!\n\n";
}

void printText(const std::filesystem::path& currentLocation, std::string& input, const std::string& username)
{
	if (input == "print" || input == "print ")
	{
		std::cout << "The path is missing!\n\n";
		return;
	}
	else if (input.substr(0, 5) == "print" && input[5] != ' ')
		return;

	input = input.substr(6, input.length() - 6);
	std::filesystem::path pathPrint = input;

	if (!isPathCorrect(input, currentLocation, username))
		return;
	if (checkPathExists(currentLocation / pathPrint))
	{
		if ((currentLocation / pathPrint).extension().string() == ".txt")
		{
			pathPrint = currentLocation / pathPrint;
		}
		else
		{
			std::cout << "The path does not represent a text file!\n\n";
			return;
		}
	}
	else if (checkPathExists(pathPrint))
	{
		//Check if the path is a text file, if it is then we can read data from it
		if (pathPrint.extension().string() == ".txt")
			pathPrint = pathPrint;
		else
		{
			std::cout << "The path does not represent a text file!\n\n";
			return;
		}
	}

	printDataFromTextFile(pathPrint);
	std::cout << "\n\n";
}

//The input should guarantee that the first 4 letters of input are "find"
//[TESTED]
bool isFindFormatGood(const std::string& input)
{
	std::string str = input;

	if (str == "find" || str == "find ")
	{
		std::cout << "The arguments for the command \"find\" are missing!\n\n";
		return 0;
	}
	else if (str[4] != ' ')
	{
		return 0;
	}
	else if (str.length() < 6)
		return 0;

	str = str.substr(5, str.length() - 5);
	if (str[0] != '"')
	{
		std::cout << "The command is incorrectly written!\n\n";
		return 0;
	}

	int j = 1;
	for (; j < str.length() && str[j] != '"'; ++j);
	if (j == str.length())
	{
		std::cout << "The command is incorrectly written!\n\n";
		return 0;
	}

	//Found the second ", new string str = "...
	str = str.substr(j, str.length() - j);
	if (str.length() == 1 || str.length() == 2 || str[1] != ' ')
	{
		std::cout << "The command is incorrectly written!\n\n";
		return 0;
	}
	str = str.substr(2, str.length() - 2);

	//It is not a problem if the path consists only of empty characters
	return 1;
}

/*
parseFindFunction

Gets a valid input in the form of a find function, returns the string in "" through text and the
path through dataLocation
[TESTED]
*/
void parseFindFunction(const std::string& input, std::string& text, std::string& dataLocationText)
{
	text = "";
	dataLocationText = "";
	int j = 0;
	for (; input[j] != '"'; ++j);
	++j;
	for (; input[j] != '"'; ++j)
		text += input[j];
	j += 2;

	for (; j < (int)input.length(); ++j)
		dataLocationText += input[j];
	return;
}

/*
findTextInTextDocument

dataLocation - location of a text file where the text is searched
text - the text that is searched
returns -1 if the text is not found, otherwise returns the line on which the text is found
[TESTED]
*/
int findTextInTextDocument(const std::string& text, const std::filesystem::path& dataLocation)
{
	std::ifstream fin(dataLocation);
	int isFound = -1;
	int textLength = text.length();

	if (fin.is_open())
	{
		std::string line;
		int lineCounter = 1;

		while (std::getline(fin, line))
		{
			int lineLength = (int)line.length();
			for (int j = 0; j < lineLength && lineLength - j >= textLength && isFound == -1; ++j)
			{
				if (line.substr(j, textLength) == text)
					isFound = lineCounter;
			}

			++lineCounter;
		}

		fin.close();
	}
	else
	{
		std::cout << "Unable to open the text file!\n\n";
	}

	return isFound;
}

void findText(const std::filesystem::path& currentLocation, std::string& input, const std::string& username)
{
	std::string text;
	std::string dataLocationText;
	std::filesystem::path dataLocation;
	
	//The function isFindFormatGood checks only whether the input is parsable with respect to the find function
	if (!isFindFormatGood(input))
		return;

	parseFindFunction(input, text, dataLocationText);
	dataLocation = dataLocationText;

	if (!isPathCorrect(dataLocation, currentLocation, username))
		return;
	if (checkPathExists(currentLocation / dataLocation))
	{
		if ((currentLocation / dataLocation).extension().string() == ".txt")
		{
			dataLocation = currentLocation / dataLocation;
		}
		else
		{
			std::cout << "The path does not represent a text file!\n\n";
			return;
		}
	}
	else if (checkPathExists(dataLocation))
	{
		//Check if the path is a text file, if it is then we can read data from it
		if (dataLocation.extension().string() == ".txt")
			dataLocation = dataLocation;
		else
		{
			std::cout << "The path does not represent a text file!\n\n";
			return;
		}
	}

	if (text.length() == 0)
	{
		std::cout << "The text that you are searching is empty!\n\n";
		return;
	}

	int lineOnWhichTextIsFound = findTextInTextDocument(text, dataLocation);
	if (lineOnWhichTextIsFound != -1)
		std::cout << "The text is found on line: " << lineOnWhichTextIsFound << "\n\n";
	else
		std::cout << "The given text is not found!\n\n";
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
		else if (input.substr(0, 4) == "list")
		{
			listDirectories(currentLocation, input, username);
		}
		else if (input.substr(0, 5) == "print")
		{
			printText(currentLocation, input, username);
		}
		else if (input.substr(0, 4) == "find")
		{
			findText(currentLocation, input, username);
		}
	}
}