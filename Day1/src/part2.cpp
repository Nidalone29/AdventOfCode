#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int main()
{
	std::vector<int> inputs;
	std::ifstream infile("input.txt");
	if (infile)
	{
		// Filling data structure (dynamic list) with input data
		std::cout << "opened input file" << std::endl;
		std::string line;
		int current, previous, i = 0, total_incements = 0;
		while (getline(infile, line))
		{
			inputs.push_back(std::stoi(line));
		}
		infile.close();

		// Actually solving the part 2 problem
		int a = 0, b = 0, result = 0;
		for (int i = 0; i < inputs.size() - 3; ++i) {
			a = inputs.at(i) + inputs.at(i + 1) + inputs.at(i + 2);
			b = inputs.at(i + 1) + inputs.at(i + 2) + inputs.at(i + 3);
			if (b > a) {
				result++;
			}
		}
		std::cout << result << std::endl;
	}
	else {
		std::cerr << "unable to open input file" << std::endl;
	}
	return 0;
}