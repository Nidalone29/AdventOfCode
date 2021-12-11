#include <fstream>
#include <iostream>
#include <queue>
#include <sstream>
#include <array>

int main()
{
	std::ifstream infile("input.txt");
	if (infile)
	{
		std::cout << "opened input file" << std::endl;
		std::string line;
		std::queue<int> random_num;
		int counter = 0, index = 0;
		std::string temp_numb;
		//all the players (vector) of cards (array 5x5)
		std::array<std::array<int, 5>, 5> card;
		std::vector<std::array<std::array<int, 5>, 5>> boards;

		while (getline(infile, line))
		{
			std::stringstream linestream(line);
			if (counter == 0) {
				//pushing the random numbers into a queue
				while (std::getline(linestream, temp_numb, ','))
				{
					random_num.push(stoi(temp_numb));
				}
				counter++;
			}
			//parsing the bingo cards (standard 5x5) 
			//https://en.wikipedia.org/wiki/Bingo_(American_version)
			else { //counter >= 1
				//new card
				//TODO praticamente non aggiunge l'ultima card e le card sono tipo shiftate di 1
				if (!line.empty()) {
					//one row
					while (std::getline(linestream, temp_numb, ' '))
					{
						if (!temp_numb.empty()) {
							card[counter - 1][index] = stoi(temp_numb);
							index++;
						}
					}
					counter++;
					index = 0;
				}
				//finished card
				else {
					boards.push_back(card);
					counter = 1;
					index = 0;
				}
			}
		}

		infile.close();

		//print the queue
		while (!random_num.empty()) {
			std::cout << random_num.front() << " ";
			random_num.pop();
		}
		std::cout << std::endl;
		//print the boards
		std::cout << "----------------------" << std::endl;
		for (auto x : boards) {
			for (int i = 0; i < x.size(); ++i) {
				for (int j = 0; j < x[i].size(); ++j) {
					std::cout << x[i][j] << " ";
				}
				std::cout << std::endl;
			}
			std::cout << "----------------------" << std::endl;
		}


	}
	else
		std::cerr << "unable to open input file" << std::endl;
	return 0;
}