#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <vector>

int main()
{
	std::ifstream infile("input.txt");
	if (infile) {
		std::cout << "opened input file" << std::endl;
		std::string line;
		std::string temp_numb;

		std::vector<int> crab_pos;
		while (getline(infile, line)) {
			std::stringstream linestream(line);
			while (std::getline(linestream, temp_numb, ',')) {
				crab_pos.push_back(stoi(temp_numb));
			}
		}

		//find the median
		std::sort(crab_pos.begin(), crab_pos.end());
		int median = (crab_pos.size() % 2 == 0)
			? (crab_pos[crab_pos.size() / 2] + crab_pos[(crab_pos.size() + 1) / 2]) / 2
			: crab_pos[(crab_pos.size() + 1) / 2];

		//calculate the fuel for reaching the median
		int fuel = 0;
		for (int x : crab_pos) {
			fuel += (x < median) ? median - x : x - median;
		}

		std::cout << "the total fuel consumed to reach position " << median << " is: " << fuel << std::endl;
		infile.close();
	}
	else {
		std::cerr << "unable to open input file" << std::endl;
	}
	return 0;
}