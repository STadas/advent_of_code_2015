#include <iostream>
#include "md5.h"

int main()
{
	std::string input = "ckczppom";
	std::string md5_str = "";
	int res1 = -1;
	int res2 = -1;
	int i = 0;
	do
	{
		md5_str = md5(input + std::to_string(i));

		if (md5_str.substr(0, 5) == "00000" && res1 == -1)
		{
			res1 = i;
		}

		res2 = i;
		i++;
	}
	while (md5_str.substr(0, 6) != "000000");
	std::cout << "part1: " << res1 << std::endl;
	std::cout << "part2: " << res2 << std::endl;

	return 0;
}