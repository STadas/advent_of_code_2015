#include <iostream>
#include <fstream>
#include <vector>

int part1(std::vector<std::string> input)
{
	int res = 0;
	std::string vowels = "aeiou";
	std::string bad[] = {"ab", "cd", "pq", "xy"};
	int bad_size = sizeof(bad) / sizeof(std::string);

	for (auto line = begin(input); line != end(input); line++)
	{
		bool nice = true;
		int count = 0;

		for (int i = 0; i < bad_size; i++)
		{
			if (line->find(bad[i]) != -1)
			{
				nice = false;
				break;
			}
		}

		if (nice)
		{
			nice = false;
			for (int i = 0; i < line->length(); i++)
			{
				for (int j = 0; j < vowels.length(); j++)
				{
					if (line->at(i) == vowels[j])
					{
						count++;
						break;
					}
				}

				if (i < line->length() - 1 && line->at(i) == line->at(i + 1))
				{
					nice = true;
				}
			}

			if (nice && count > 2)
			{
				res++;
			}
		}
	}
	return res;
}

int part2 (std::vector<std::string> input)
{
	int res = 0;
	for (auto line = begin(input); line != end(input); line++)
	{
		bool nice = false;

		for (int i = 0; i < line->length() - 1; i++)
		{
			std::string two = std::string() + line->at(i) + line->at(i + 1);
			if (line->find(two, i + 2) != -1)
			{
				nice = true;
				break;
			}
		}
		if (nice)
		{
			for (int i = 0; i < line->length() - 2; i++)
			{
				if (line->at(i) == line->at(i + 2))
				{
					res++;
					break;
				}
			}
		}
	}

	return res;
}

int main()
{
	std::string line = "";

	std::ifstream fin;
	fin.open("day5input");
	std::vector<std::string> input;

	while (getline(fin, line))
	{
		input.push_back(line);
	}


	fin.close();
	std::cout << "part1: " << part1(input) << std::endl;
	std::cout << "part2: " << part2(input) << std::endl;
}