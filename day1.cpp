#include <iostream>
#include <fstream>

int main()
{
	std::string input = "";
	int floor = 0;
	bool basement = false;

	std::ifstream fin;
	fin.open("day1input");
	std::getline(fin, input);
	fin.close();

	for (int i = 0; i < input.length(); i++)
	{
		if (input[i] == '(')
		{
			floor++;
		}
		else if (input[i] == ')')
		{
			floor--;
		}

		if (!basement && floor < 0)
		{
			std::cout << "part2: " << i + 1 << std::endl;
			basement = true;
		}
	}

	std::cout << "part1: " << floor << std::endl;

	return 0;
}