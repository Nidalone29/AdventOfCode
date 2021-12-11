#include <fstream>
#include <iostream>
#include <vector>
#include <math.h>

int binary_to_decimal(const std::string& input)
{
	int result = 0;
	for (int i = input.size() - 1; i != -1; i--) {
		if (input[i] == '1')
			result += pow(2, (input.size() - i - 1));
	}
	return result;
}

int main()
{
	std::ifstream infile("input.txt");
	if (infile)
	{
		std::cout << "opened input file" << std::endl;
		std::string line;
		std::vector<int> values;
		bool initialization = false;
		while (getline(infile, line))
		{
			//first iteration
			if (!initialization) {
				for (int i = 0; i < line.size(); ++i) {
					values.push_back(0);
				}
				initialization = true;
			}

			//counting 0
			for (int i = 0; i < line.size(); ++i) {
				if (line.at(i) == '0')
					values[i]++;
			}
		}
		infile.close();

		std::string gammarate = "", epsilonrate = "";
		for (int x : values) {
			//there are more 0
			if (x > values.size() / 2) {
				gammarate += '0';
				epsilonrate += '1';
			}
			else {
				gammarate += '1';
				epsilonrate += '0';
			}
		}
		std::cout << "binary gammarate: " << binary_to_decimal(gammarate) << std::endl;
		std::cout << "binary epsilonrate: " << binary_to_decimal(epsilonrate) << std::endl;
		std::cout << "power consumption: " <<
			binary_to_decimal(gammarate) * binary_to_decimal(epsilonrate) << std::endl;
	}
	else {
		std::cerr << "unable to open input file" << std::endl;
	}
	return 0;
}