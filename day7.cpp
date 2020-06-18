#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>

using string = std::string;
using uint16 = uint16_t;

enum OPS
{
	OP_AND, OP_OR, OP_NOT, OP_LSHIFT, OP_RSHIFT, OP_ERR
};

std::vector<std::vector<string>> get_input();
OPS stoop(const string s);
uint16_t get_num(const string s, std::map<string, uint16_t> wire);
void do_not(std::vector<string> line, std::map<string, uint16_t> &wire, std::map<string, bool> &wire_ch);
void do_assign(std::vector<string> line, std::map<string, uint16_t> &wire, std::map<string, bool> &wire_ch);
void do_switch(std::vector<string> line, std::map<string, uint16_t> &wire, std::map<string, bool> &wire_ch);

int calc(std::vector<std::vector<string>> input, const bool part2, const uint16_t p2int = 0);

int main()
{
	std::vector<std::vector<string>> input = get_input();

	uint16_t p1 = calc(input, false);

	std::cout << "part1: " << p1 << std::endl;
	std::cout << "part2: " << calc(input, true, p1) << std::endl;

	return 0;
}

std::vector<std::vector<string>> get_input()
{
	std::ifstream fin;
	std::vector<std::vector<string>> input;
	string line = "";

	fin.open("day7input");
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

int calc(std::vector<std::vector<string>> input, const bool part2, const uint16_t p2int)
{
	std::map<string, uint16_t> wire;
	std::map<string, bool> wire_ch;
	
	for(auto line : input)
	{
		wire[line.back()] = 0;
		wire_ch[line.back()] = 0;
	}

	if(part2)
	{
		wire["b"] = p2int;
		wire_ch["b"] = 1;
	}

	while(wire_ch["a"] == 0)
	{
		for(auto line : input)
		{
			if(wire_ch["a"] == 1)
			{
				break;
			}
			if(wire_ch[line.back()] == 0)
			{
				if(stoop(line[0]) == OP_NOT)
				{
					do_not(line, wire, wire_ch);
				}
				else if(line[1] == "->")
				{
					do_assign(line, wire, wire_ch);
				}
				else
				{
					do_switch(line, wire, wire_ch);
				}
			}
		}
	}

	return wire["a"];
}

OPS stoop(const string s)
{
	if( s=="AND")
		return OP_AND;
	else if(s=="OR")
		return OP_OR;
	else if(s=="LSHIFT")
		return OP_LSHIFT;
	else if(s=="RSHIFT")
		return OP_RSHIFT;
	else if(s=="NOT")
		return OP_NOT;
	else
		return OP_ERR;
}

uint16_t get_num(const string s, std::map<string, uint16_t> wire)
{
	if(isdigit(s[0]))
	{
		return std::stoi(s);
	}
	else
	{
		return wire[s];
	}
}

void do_not(std::vector<string> line, std::map<string, uint16_t> &wire, std::map<string, bool> &wire_ch)
{
	if((wire_ch[line[1]] == 1 || isdigit(line[1][0])))
	{
		uint16_t a = get_num(line[1], wire);
		wire[line.back()] = ~a;
		wire_ch[line.back()] = 1;
	}
}

void do_assign(std::vector<string> line, std::map<string, uint16_t> &wire, std::map<string, bool> &wire_ch)
{
	if((wire_ch[line[0]] == 1 || isdigit(line[0][0])))
	{
		uint16_t a = get_num(line[0], wire);
		wire[line.back()] = a;
		wire_ch[line.back()] = 1;
	}
}

void do_switch(std::vector<string> line, std::map<string, uint16_t> &wire, std::map<string, bool> &wire_ch)
{
	if((wire_ch[line[0]] == 1 || isdigit(line[0][0])) && (wire_ch[line[2]] == 1 || isdigit(line[2][0])))
	{
		uint16_t a = get_num(line[0], wire);
		uint16_t b = get_num(line[2], wire);

		switch(stoop(line[1]))
		{
			case OP_AND:
			{
				wire[line.back()] = a & b;
				wire_ch[line.back()] = 1;
				break;
			}
			case OP_OR:
			{
				wire[line.back()] = a | b;
				wire_ch[line.back()] = 1;
				break;
			}
			case OP_LSHIFT:
			{
				wire[line.back()] = a << b;
				wire_ch[line.back()] = 1;
				break;
			}
			case OP_RSHIFT:
			{
				wire[line.back()] = a >> b;
				wire_ch[line.back()] = 1;
				break;
			}
			default:
			{
				break;
			}
		}
	}
}