#include <iostream>
#include <fstream>
#include <vector>

void give_present(int x_pos, int y_pos, int &res, std::vector<std::vector<bool>> &grid)
{
	if (grid[x_pos][y_pos] == false)
	{
		res++;
		grid[x_pos][y_pos] = true;
	}
}

int calc (bool p2)
{
	std::vector<bool> init(1, false);
	std::vector<std::vector<bool>> grid(1, init);
	int x_pos = 0, y_pos = 0;
	int x2_pos = 0, y2_pos = 0;
	int res = 0;

	std::string input = "";
	std::ifstream fin;
	fin.open("day3input");
	std::getline(fin, input);
	fin.close();

	for (int i = 0; i < input.length(); i++)
	{
		switch (input[i])
		{
		case '^':
		{
			if (y_pos == 0)
			{
				for (auto it = begin(grid); it != end(grid); ++it)
				{
					it->insert(it->begin(), false);
				}
				y2_pos++;
			}
			else
			{
				y_pos--;
			}

			give_present(x_pos, y_pos, res, grid);
			break;
		}
		case 'v':
		{
			if (y_pos == grid[0].size() - 1)
			{
				for (auto it = begin(grid); it != end(grid); ++it)
				{
					it->push_back(false);
				}
			}
			y_pos++;

			give_present(x_pos, y_pos, res, grid);
			break;
		}
		case '<':
		{
			if (x_pos == 0)
			{
				std::vector<bool> prev_x(grid[0].size(), false);
				grid.insert(grid.begin(), prev_x);
				x2_pos++;
			}
			else
			{
				x_pos--;
			}

			give_present(x_pos, y_pos, res, grid);
			break;
		}
		case '>':
		{
			if (x_pos == grid.size() - 1)
			{
				std::vector<bool> next_x(grid[0].size(), false);
				grid.push_back(next_x);
			}
			x_pos++;

			give_present(x_pos, y_pos, res, grid);
			break;
		}
		}

		if (p2)
		{
			int x_temp = x_pos;
			int y_temp = y_pos;

			x_pos = x2_pos;
			y_pos = y2_pos;

			x2_pos = x_temp;
			y2_pos = y_temp;

		}
	}

	return res;
}

int main()
{
	std::cout << "part1: " << calc(0) << std::endl;
	std::cout << "part2: " << calc(1) << std::endl;

	return 0;
}