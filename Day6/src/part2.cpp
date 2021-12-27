#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <array>

void updatestate(std::array<long, 9>& fishes_status)
{
	long numday0 = fishes_status[0];

	//basically a left shift for decrementing the day
	for (int i = 1; i < fishes_status.size(); ++i) {
		fishes_status[i - 1] = fishes_status[i];
	}
	//reset the timer for fishes that gave birth to a new fish
	fishes_status[6] += numday0;
	//all the newborns
	fishes_status[8] = numday0;
}

int main()
{
	std::ifstream infile("input.txt");
	if (infile) {
		std::cout << "opened input file" << std::endl;
		std::string line;
		std::string temp_numb;

		//we store how many fishes exists per possible day
		std::array<long, 9> fishes_status = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };

		while (getline(infile, line)) {
			std::stringstream linestream(line);
			while (std::getline(linestream, temp_numb, ',')) {
				fishes_status[stoi(temp_numb)]++;
			}
		}

		//for 256 days we iterate trhu the fishes
		const int days = 256;
		for (int i = 1; i <= days; ++i) {
			updatestate(fishes_status);
		}

		//counting the total fishes
		long total_fishes = 0;
		for (long x : fishes_status) {
			total_fishes += x;
		}

		std::cout << "number of fishes: " << total_fishes << std::endl;

		infile.close();
	}
	else {
		std::cerr << "unable to open input file" << std::endl;
	}
	return 0;
}