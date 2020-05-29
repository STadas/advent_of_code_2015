#include <iostream>
#include <fstream>
#include <vector>

int calc (bool p2)
{
	std::vector<bool> init(1, false);
	std::vector<std::vector<bool>> grid(1, init);
	int x_pos = 0, y_pos = 0;
	int x1_pos = 0, x2_pos = 0, y1_pos = 0, y2_pos = 0;
	int res = 0;

	std::string input = "";
	std::ifstream fin;
	fin.open("day3input");
	std::getline(fin, input);
	fin.close();

	for (int i = 0; i < input.length(); i++)
	{
		if (p2)
		{
			if (i % 2 == 0)
			{
				x2_pos = x_pos;
				y2_pos = y_pos;

				x_pos = x1_pos;
				y_pos = y1_pos;

				if (i < 20)
					std::cout << "santa_pos [" << x_pos << "," << -1 * y_pos << "]" << std::endl;
			}
			else
			{
				x1_pos = x_pos;
				y1_pos = y_pos;

				x_pos = x2_pos;
				y_pos = y2_pos;

				if (i < 20)
					std::cout << "bot_pos [" << x_pos << "," << -1 * y_pos << "]" << std::endl;
			}
		}

		if (grid[x_pos][y_pos] == false)
		{
			res++;
			grid[x_pos][y_pos] = true;
		}

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
			}
			else
			{
				y_pos--;
			}
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
			break;
		}
		case '<':
		{
			if (x_pos == 0)
			{
				std::vector<bool> prev_x(grid[0].size(), false);
				grid.insert(grid.begin(), prev_x);
			}
			else
			{
				x_pos--;
			}
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
			break;
		}
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