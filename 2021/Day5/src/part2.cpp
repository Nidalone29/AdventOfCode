#include <fstream>
#include <iostream>
#include <string>
#include <regex>
#include <array>
#include <cmath>

struct cartesian_plane {
	//kinda "cheating" that i am assuming the grid size at 1000...
	std::array<std::array<int, 1000>, 1000> plane;
	cartesian_plane(int init_value)
	{
		for (int i = 0; i < plane.size(); ++i) {
			for (int j = 0; j < plane[0].size(); ++j) {
				plane[i][j] = init_value;
			}
		}
	}
};

struct point {
	int x, y;
	point(int x, int y)
		:x(x), y(y)
	{

	}
};

struct hydrotermal_vent {
	point p1, p2;
	hydrotermal_vent(int x1, int y1, int x2, int y2)
		:p1(point(x1, y1)), p2(point(x2, y2))
	{

	}
};

void draw_line(hydrotermal_vent& ht, cartesian_plane& of)
{
	//check for the possible swapped point
	//i do this so i have to write half of the for loops
	int rise = ht.p2.y - ht.p1.y;
	int run = ht.p2.x - ht.p1.x;
	if ((run < 0 && rise == 0) || (run == 0 && rise < 0) ||
		(rise < 0 && run < 0) || (rise > 0 && run < 0)) {
		std::swap(ht.p1, ht.p2);
	}
	//recompute rise and run
	rise = ht.p2.y - ht.p1.y;
	run = ht.p2.x - ht.p1.x;

	//undefined slope -- vertical line
	if (run == 0 /*&& any rise*/) {
		std::cout << "undefined slope () " << std::endl;
		for (int i = ht.p1.y; i <= ht.p2.y; ++i) {
			of.plane[ht.p1.x][i]++;
		}
	}
	//zero slope (0) -- horizontal line
	else if (rise == 0) {
		std::cout << "zero slope (0) " << std::endl;
		for (int i = ht.p1.x; i <= ht.p2.x; ++i) {
			of.plane[i][ht.p1.y]++;
		}
	}
	//positive slope (+1 because only 45deg) (both x and y increments)
	else if (rise > 0 && run > 0) {
		std::cout << "positive slope (+1) " << run << std::endl;
		int x = ht.p1.x;
		int y = ht.p1.y;
		for (int i = 0; i <= run; ++i) {
			of.plane[x][y]++;
			x++;
			y++;
		}
	}
	//negative slope (-1 because only 45deg) (x increments and y decrements)
	else if (rise < 0 && run > 0) {
		std::cout << "negative slope (-1) " << run << std::endl;
		int x = ht.p1.x;
		int y = ht.p1.y;
		for (int i = 0; i <= run; ++i) {
			of.plane[x][y]++;
			x++;
			y--;
		}
	}
}

int main()
{
	std::ifstream infile("input.txt");
	if (infile) {
		std::cout << "opened input file" << std::endl;
		std::string line;
		std::cmatch match;
		std::regex regex_hydrotermal_vents(R"(([\d]*),([\d]*) -> ([\d]*),([\d]*))");
		std::vector<hydrotermal_vent> hydrotermal_vents;
		while (getline(infile, line)) {
			std::regex_match(line.c_str(), match, regex_hydrotermal_vents);
			//x1, y1 -> x2, y2
			if (match.size() > 0) {
				hydrotermal_vents.push_back(hydrotermal_vent(
					stoi(match.str(1)), stoi(match.str(2)),
					stoi(match.str(3)), stoi(match.str(4))
				));
			}
		}
		infile.close();

		cartesian_plane ocean_floor(0);
		//draw all the hydrotermal vents on the ocean floor
		for (hydrotermal_vent ht : hydrotermal_vents) {
			draw_line(ht, ocean_floor);
		}

		int number_of_overlaps = 0;
		//count the overlapping vents
		for (int i = 0; i < ocean_floor.plane.size(); ++i) {
			for (int j = 0; j < ocean_floor.plane[0].size(); ++j) {
				if (ocean_floor.plane[i][j] > 1) {
					number_of_overlaps++;
				}
			}
		}

		//final result
		std::cout << "the number of overlaps is " << number_of_overlaps << std::endl;
	}
	else {
		std::cerr << "unable to open input file" << std::endl;
	}
	return 0;
}