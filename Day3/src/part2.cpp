#include <fstream>
#include <iostream>
#include <vector>
#include <math.h>

std::string filtering(char bit, std::vector<std::string>& inputs, int index)
{
	for (auto it = inputs.begin(); it != inputs.end(); ) {
		if ((*it)[index] != bit)
			it = inputs.erase(it);
		else
			++it;
		if (inputs.size() == 1)
			return *inputs.begin();
	}
	return "";
}

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

		//the report of the submarine
		std::vector<std::string> oxygen;
		std::vector<std::string> co2;
		//ox most common, co2 least common
		int oxygen_gen, co2_scrub;

		//grabbing the input into a dynamic list
		std::string line;
		while (getline(infile, line))
		{
			oxygen.push_back(line);
			co2.push_back(line);
		}
		infile.close();

		//oxygen
		const int number_of_bits = oxygen[0].size();
		int number_of_0 = 0;
		std::string resultox = "";

		for (int i = 0; (i < number_of_bits); ++i) {
			for (std::string x : oxygen) {
				if (x[i] == '0')
					number_of_0++;
			}
			//there are more 0
			if (number_of_0 > oxygen.size() / 2)
				resultox = filtering('0', oxygen, i);
			//there are more 1 or 0 and 1 are the same
			else
				resultox = filtering('1', oxygen, i);

			//check if we have finished
			if (resultox != "")
				oxygen_gen = binary_to_decimal(resultox);

			//reset the counter
			number_of_0 = 0;
		}

		//co2
		number_of_0 = 0;
		std::string resultco2 = "";
		for (int i = 0; (i < number_of_bits); ++i) {
			for (std::string x : co2) {
				if (x[i] == '0')
					number_of_0++;

			}
			if (number_of_0 > co2.size() / 2)
				resultco2 = filtering('1', co2, i);
			else
				resultco2 = filtering('0', co2, i);

			if (resultco2 != "")
				co2_scrub = binary_to_decimal(resultco2);

			//reset the counter
			number_of_0 = 0;
		}
		std::cout << "oxygen_gen " << oxygen_gen << std::endl;
		std::cout << "co2_scrub " << co2_scrub << std::endl;

		std::cout << "life supply " << oxygen_gen * co2_scrub << std::endl;
	}
	else
		std::cerr << "unable to open input file" << std::endl;
	return 0;
}