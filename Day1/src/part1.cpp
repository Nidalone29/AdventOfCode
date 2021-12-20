#include <fstream>
#include <iostream>
#include <string>

int main()
{
	std::ifstream infile("input.txt");
	if (infile) {
		std::cout << "opened input file" << std::endl;
		std::string line;
		int current, previous, i = 0, total_incements = 0;
		while (getline(infile, line)) {
			if (i != 0) {
				current = std::stoi(line);
				if (current > previous) {
					total_incements++;
				}
			}
			previous = std::stoi(line);
			i++;
		}
		infile.close();
		std::cout << total_incements << std::endl;
	}
	else {
		std::cerr << "unable to open input file" << std::endl;
	}
	return 0;
}