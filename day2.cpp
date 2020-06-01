#include <iostream>
#include <fstream>
#include <sstream>

int main()
{
	std::ifstream fin;
	fin.open("day2input");

	std::string line = "";
	int res_1 = 0;
	int res_2 = 0;

	while (getline(fin, line))
	{
		std::stringstream ss(line);

		int d[3];
		int s[3];
		int p[3];

		for (int i = 0; i < 3; i++)
		{
			std::string dimen = "";
			getline(ss, dimen, 'x');
			d[i] = std::stoi(dimen);
		}

		s[0] = 2 * d[0] * d[1];
		s[1] = 2 * d[1] * d[2];
		s[2] = 2 * d[2] * d[0];

		int smallest_s = s[0];

		for (int i = 0; i < 3; i++)
		{
			res_1 += s[i];
			if (smallest_s > s[i])
			{
				smallest_s = s[i];
			}
		}
		res_1 += smallest_s / 2;

		p[0] = 2 * (d[0] + d[1]);
		p[1] = 2 * (d[1] + d[2]);
		p[2] = 2 * (d[2] + d[0]);

		int smallest_p = p[0];

		for (int i = 0; i < 3; i++)
		{
			if (smallest_p > p[i])
			{
				smallest_p = p[i];
			}
		}
		res_2 += smallest_p + d[0] * d[1] * d[2];
	}

	fin.close();

	std::cout << "part1: " << res_1 << std::endl;
	std::cout << "part2: " << res_2 << std::endl;


	return 0;
}