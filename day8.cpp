#include <iostream>
#include <fstream>
#include <vector>

using string = std::string;

std::vector<string> get_input();
int calc(std::vector<string> input, bool part2 = false);

int main()
{
	std::vector<string> input = get_input();

	std::cout << "part1: " << calc(input) << std::endl;
	std::cout << "part2: " << calc(input, true) << std::endl;
}

std::vector<string> get_input()
{
	std::vector<string> input;
	string line = "";
	std::ifstream fin;

	fin.open("day8input");
	while (getline(fin, line))
	{
		input.push_back(line);
	}
	fin.close();

	return input;
}

int calc(std::vector<string> input, bool part2)
{
	int res = 0;
	int resp2 = 0;

	for (auto line : input)
	{
		int p2encode = 0;
		int storedlen = 0;
		for (int i = 0; i < line.length(); i++)
		{
			if (line[i] == '\\')
			{
				switch (line[i + 1])
				{
					case '\\':
					{
						p2encode += 2;
						i++;
						break;
					}
					case '\"':
					{
						p2encode += 2;
						i++;
						break;
					}
					default:
					{
						p2encode++;
						i += 3;
					}
				}
			}
			storedlen++;
		}
		res += line.length() - storedlen + 2;
		resp2 += 4 + p2encode;
	}

	return !part2 ? res : resp2;
}