#include "tests.h"

void pathExistsTests()
{
	std::vector< std::pair<bool, bool> > vec;
	vec.push_back(std::make_pair(checkPathExists(""), 0));
	vec.push_back(std::make_pair(checkPathExists("fdsa fojds aoifjdisoa jfoisda jfoisda jiofsdaj iofsdjaio fjdsaio fjsdoai jfiosdaj fiodsaj iofsdaj iofsdaj iofsdjaio fjsdaio fjdsioa jfisdoa jfiodsa jfidosaj fosdaj iofdsaj iofdjsaio fjdsioa jfiosda jifoewj ruiweiq tr weuqbntu erqbtueoqr bguz erbhjxvy bfb aduzfb uzawr"), 0));
	vec.push_back(std::make_pair(checkPathExists("C:/oosproject/users/"), 1));
	vec.push_back(std::make_pair(checkPathExists("C:/oosproject/users/admin/dve reci"), 1));

	//THIS TEST THROWS AN EXCEPTION
	//	vec.push_back(std::make_pair(checkPathExists("\"C:/oosproject/users/\""), 1));

	for (int i = 0; i < (int)vec.size(); ++i)
	{
		if (vec[i].first != vec[i].second)
		{
			std::cout << "ERROR; TEST " << i << "\n";
		}
	}
}

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
