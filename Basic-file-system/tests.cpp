#include "tests.h"

void printVector(std::vector<std::string>& vec)
{
	for (int i = 0; i < (int)vec.size(); ++i)
		std::cout << vec[i] << "\n";
	std::cout << "\n";
}

void parseInputLineTests()
{
	std::vector<std::string> ans;
//	parseInputLine(ans, "\""); THROWS EXCEPTION
	parseInputLine(ans, "     cd     ");
	printVector(ans);
	parseInputLine(ans, " \"cd\" gg \"   fff fgggg      \" ggw  wwgwgw gwgw");
	printVector(ans);
	parseInputLine(ans, "           ");
	printVector(ans);
	parseInputLine(ans, "\"\"");
	printVector(ans);
}
