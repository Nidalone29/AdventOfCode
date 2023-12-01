#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <cmath>

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

		//find the avarage
		int sum = 0;
		for (int x : crab_pos) {
			sum += x;
		}
		int avg = sum / crab_pos.size();

		//we compute the fuel consumption to reach the avg
		int fuel = 0;
		int distance = 0;
		for (int x : crab_pos) {
			distance = (x < avg) ? avg - x : x - avg;
			//https://en.wikipedia.org/wiki/1_%2B_2_%2B_3_%2B_4_%2B_%E2%8B%AF
			fuel += (distance * (distance + 1)) / 2;
		}

		std::cout << "the total fuel consumed to reach position " << avg << " is: " << fuel << std::endl;
		infile.close();
	}
	else {
		std::cerr << "unable to open input file" << std::endl;
	}
	return 0;
}