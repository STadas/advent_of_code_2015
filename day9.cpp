#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <map>

using string = std::string;

std::vector<std::vector<string>> get_input();
int calc(std::vector<std::vector<string>> input, bool part2 = false);

int main()
{
	std::vector<std::vector<string>> input = get_input();

	std::cout << "part1: " << calc(input) << std::endl;
	std::cout << "part1: " << calc(input, true) << std::endl;

	return 0;
}

std::vector<std::vector<string>> get_input()
{
	std::ifstream fin;
	std::vector<std::vector<string>> input;
	string line = "";

	fin.open("day9input");
	while (getline(fin, line))
	{
		std::vector<string> temp_vec;
		std::istringstream ss(line);
		string temp_str;

		while (getline(ss, temp_str, ' '))
		{
			temp_vec.push_back(temp_str);
		}
		input.push_back(temp_vec);
	}
	fin.close();

	return input;
}

int calc(std::vector<std::vector<string>> input, bool part2)
{
	std::map<string, std::map<string, int>> routes;
	std::vector<std::string> cities;

	int shortest = INT32_MAX;
	int longest = 0;

	for (auto line : input)
	{
		routes[line[0]][line[2]] = routes[line[2]][line[0]] = std::stoi(line.back());
	}

	for (auto it : routes)
	{
		cities.push_back(it.first);
	}

	do
	{
		int curr = 0;
		for (auto it = cities.begin(); it != cities.end() - 1; it++)
		{
			curr += routes[*it][*(it + 1)];
		}

		shortest = std::min(curr, shortest);
		longest = std::max(curr, longest);
	}
	while (std::next_permutation(cities.begin(),  cities.end()));

	return !part2 ? shortest : longest;
}