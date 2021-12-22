#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

void updatestate(std::vector<int>& lanternfishes)
{
	int newfishes = 0;
	for (int i = 0; i < lanternfishes.size(); ++i) {
		lanternfishes[i]--;
		if (lanternfishes[i] == -1) {
			lanternfishes[i] = 6;
			newfishes++;
		}
	}
	for (int i = 0; i < newfishes; ++i) {
		lanternfishes.push_back(8);
	}
}

int main()
{
	std::ifstream infile("input.txt");
	if (infile) {
		std::cout << "opened input file" << std::endl;
		std::string line;
		std::vector<int> lanternfishes;
		std::string temp_numb;
		while (getline(infile, line)) {
			std::stringstream linestream(line);
			while (std::getline(linestream, temp_numb, ',')) {
				lanternfishes.push_back(stoi(temp_numb));
			}
		}

		//for 80 days
		const int days = 80;
		for (int i = 1; i <= days; ++i) {
			updatestate(lanternfishes);
			std::cout << "after day " << i << " -- number of fishes: " << lanternfishes.size() << std::endl;
		}

		infile.close();
	}
	else {
		std::cerr << "unable to open input file" << std::endl;
	}
	return 0;
}