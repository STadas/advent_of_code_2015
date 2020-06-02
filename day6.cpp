#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

const int grid_size = 1000;
bool **grid1;
int **grid2;


int getCoord(std::stringstream &ss, std::string &coord, std::string &input_substr, int incr, char symbol)
{
	getline(ss, coord, symbol);
	int coord_int = std::stoi(coord);
	input_substr = input_substr.substr(coord.length() + incr);
	return coord_int;
}

void turn_on(int x1, int y1, int x2, int y2)
{
	for (int i = x1; i <= x2; i++)
	{
		for (int j = y1; j <= y2; j++)
		{
			grid1[i][j] = 1;
			grid2[i][j] ++;
		}
	}
}

void turn_off(int x1, int y1, int x2, int y2)
{
	for (int i = x1; i <= x2; i++)
	{
		for (int j = y1; j <= y2; j++)
		{
			grid1[i][j] = 0;
			if (grid2[i][j] > 0)
			{
				grid2[i][j] --;
			}
		}
	}
}

void toggle(int x1, int y1, int x2, int y2)
{
	for (int i = x1; i <= x2; i++)
	{
		for (int j = y1; j <= y2; j++)
		{
			if (grid1[i][j] == 1)
			{
				grid1[i][j] = 0;
			}
			else
			{
				grid1[i][j] = 1;
			}
			grid2[i][j] += 2;
		}
	}
}

int calc(std::vector<std::string> input, bool part2)
{
	int res = 0;
	grid1 = new bool *[grid_size];
	grid2 = new int *[grid_size];
	for (int i = 0; i < grid_size; i++)
	{
		grid1[i] = new bool[grid_size];
		grid2[i] = new int[grid_size];
	}

	std::string instr[] = {"turn on", "turn off", "toggle"};
	int instr_size = sizeof(instr) / sizeof(std::string);

	for (int i = 0; i < input.size(); i++)
	{
		for (int j = 0; j < instr_size; j++)
		{
			if (input[i].find(instr[j]) != -1)
			{
				int index = instr[j].length() + 1;

				std::string coord;
				std::string input_substr = input[i].substr(index);
				std::stringstream ss(input_substr);

				int x1 = getCoord(ss, coord, input_substr, 1, ',');
				int y1 = getCoord(ss, coord, input_substr, 9, ' ');
				ss.clear();
				ss.str(input_substr);
				int x2 = getCoord(ss, coord, input_substr, 1, ',');
				int y2 = getCoord(ss, coord, input_substr, 0, '\n');

				//printf("[%d;%d] - [%d;%d]\n", x1, y1, x2, y2);

				if (instr[j] == "turn on")
				{
					turn_on(x1, y1, x2, y2);
				}
				else if (instr[j] == "turn off")
				{
					turn_off(x1, y1, x2, y2);
				}
				else if (instr[j] == "toggle")
				{
					toggle(x1, y1, x2, y2);
				}

				break;
			}
		}
	}

	for (int i = 0; i < grid_size; i++)
	{
		for (int j = 0; j < grid_size; j++)
		{
			if (grid1[i][j] == 1 && !part2)
			{
				res++;
			}
			else if (part2)
			{
				res += grid2[i][j];
			}
		}
	}

	return res;
}

int main()
{
	std::ifstream fin;
	fin.open("day6input");
	std::vector<std::string> input;
	std::string line = "";

	while (getline(fin, line))
	{
		input.push_back(line);
	}
	fin.close();

	std::cout << "part1: " << calc(input, 0) << std::endl;
	std::cout << "part2: " << calc(input, 1) << std::endl;
}