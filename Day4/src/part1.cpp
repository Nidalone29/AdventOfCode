#include <fstream>
#include <iostream>
#include <sstream>
#include <queue>
#include <array>

typedef std::array<std::array<int, 5>, 5> player_card;

int computesolution(const player_card& card, int winning_guess)
{
	int result = 0;
	for (int i = 0; i < card.size(); ++i) {
		for (int j = 0; j < card[i].size(); ++j) {
			if (card[i][j] != -1)
				result += card[i][j];
		}
	}
	return result * winning_guess;
}

bool checkplayerwin(const player_card& card)
{
	int complete_column = 0;
	int complete_row = 0;
	//check complete rows
	for (int i = 0; i < card.size(); ++i) {
		for (int j = 0; j < card[i].size(); ++j) {
			if (card[i][j] == -1)
				complete_row++;
			else if (card[j][i] == -1)
				complete_column++;
		}
		if (complete_row == 5 || complete_column == 5)
			return true;
		complete_row = 0;
		complete_column = 0;
	}
	return false;
}

player_card playgame(std::vector<player_card>& boards, int guess)
{
	for (int x = 0; x < boards.size(); ++x) {
		for (int i = 0; i < boards[x].size(); ++i) {
			for (int j = 0; j < boards[x][i].size(); ++j) {
				if (boards[x][i][j] == guess) {
					boards[x][i][j] = -1;
					if (checkplayerwin(boards[x])) {
						return boards[x];
					}
				}
			}
		}
	}
	player_card lost;
	lost.fill({ {0, 0, 0, 0, 0} });
	return lost;
}

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
		player_card card;
		std::vector<player_card> boards;
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
				if (counter > 5) {
					boards.push_back(card);
					counter = 1;
					index = 0;
				}
			}
		}

		infile.close();

		//play the game
		player_card winner;
		winner.fill({ {0, 0, 0, 0, 0} });

		bool gamewon = false;
		while (!random_num.empty() && !gamewon) {
			winner = playgame(boards, random_num.front());
			if (winner[0][0] != 0) {
				gamewon = true;
				int result = computesolution(winner, random_num.front());
				std::cout << "game won at " << random_num.front() << std::endl;
				std::cout << "the final result is " << result << std::endl;
			}
			std::cout << random_num.front() << " ";
			random_num.pop();
		}
	}
	else
		std::cerr << "unable to open input file" << std::endl;
	return 0;
}