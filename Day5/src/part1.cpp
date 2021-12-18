#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <regex>
#include <vector>
#include <array>
#include <algorithm>
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

int main()
{
	std::ifstream infile("input.txt");
	if (infile)
	{
		std::cout << "opened input file" << std::endl;
		std::string line;
		std::cmatch match;
		std::regex regex_hydrotermal_vents(R"(([\d]*),([\d]*) -> ([\d]*),([\d]*))");
		std::vector<hydrotermal_vent> hydrotermal_vents;
		while (getline(infile, line))
		{
			std::regex_match(line.c_str(), match, regex_hydrotermal_vents);
			//x1, y1 -> x2, y2
			if (match.size() > 0) {
				std::cout << "poggers" << std::endl;
				hydrotermal_vents.push_back(hydrotermal_vent(
					stoi(match.str(1)), stoi(match.str(2)),
					stoi(match.str(3)), stoi(match.str(4))
				));
			}
		}
		infile.close();

		cartesian_plane ocean_floor(0);
		int total_distance = 0;
		int x_distance = 0, y_distance = 0;
		//locate all teh hydrotermal vents on the ocean floor
		for (hydrotermal_vent ht : hydrotermal_vents) {
			std::cout << ht.p1.x << "," << ht.p1.y << " -> " << ht.p2.x << "," << ht.p2.y << std::endl;
			//compute distance
			x_distance = ht.p1.x - ht.p2.x;
			y_distance = ht.p1.y - ht.p2.y;
			//"draw" the vent on the ocean
			if (x_distance == 0) {
				if (std::max(ht.p1.y, ht.p2.y) == ht.p1.y) {
					for (int i = ht.p2.y; i <= ht.p1.y; ++i) {
						ocean_floor.plane[ht.p1.x][i]++;
					}
				}
				else {
					for (int i = ht.p1.y; i <= ht.p2.y; ++i) {
						ocean_floor.plane[ht.p1.x][i]++;
					}
				}
			}
			else if (y_distance == 0) {
				if (std::max(ht.p1.x, ht.p2.x) == ht.p1.x) {
					for (int i = ht.p2.x; i <= ht.p1.x; ++i) {
						ocean_floor.plane[i][ht.p1.y]++;
					}
				}
				else {
					for (int i = ht.p1.x; i <= ht.p2.x; ++i) { //north
						ocean_floor.plane[i][ht.p1.y]++;
					}
				}
			}
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

		std::cout << "the number of overlaps is " << number_of_overlaps << std::endl;

	}
	else {
		std::cerr << "unable to open input file" << std::endl;
	}
	return 0;
}