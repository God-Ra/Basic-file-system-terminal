#include <iostream>
#include "gline.h"


int main()
{
	std::string input = "";

	while (input != "g")
	{
		getLineAsterisks(input, 31, "Password: ");
	}
}