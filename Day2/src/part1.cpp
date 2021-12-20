#include <fstream>
#include <iostream>

int main()
{
	std::ifstream infile("input.txt");
	if (infile) {
		std::cout << "opened input file" << std::endl;
		std::string line;
		int horizontal = 0, depth = 0;
		std::string direction;
		int int_value;
		while (getline(infile, line)) {
			direction = line.substr(0, line.find(' '));
			int_value = std::stoi(line.substr(line.find(' '), '\n'));
			if (direction == "forward")
				horizontal += int_value;
			else if (direction == "up")
				depth -= int_value;
			else if (direction == "down")
				depth += int_value;
		}
		infile.close();
		std::cout << horizontal * depth << std::endl;
	}
	else {
		std::cerr << "unable to open input file" << std::endl;
	}
	return 0;
}