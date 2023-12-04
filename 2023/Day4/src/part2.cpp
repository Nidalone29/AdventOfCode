#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

std::vector<std::string> split(const std::string& input, const std::string x) {
  std::vector<std::string> output;
  std::string to_tokenize = input;

  while (to_tokenize.find(x) != std::string::npos) {
    output.push_back(to_tokenize.substr(0, to_tokenize.find(x)));
    to_tokenize = to_tokenize.substr(to_tokenize.find(x) + x.size());
  }
  output.push_back(to_tokenize);

  return output;
}

std::vector<int> get_numbers(const std::string& input) {
  std::vector<int> output;
  const int size = input.length();

  for (int i = 0; i < size; i++) {
    if (std::isdigit(input[i])) {
      std::string svalue = "";
      svalue += input[i];
      int newi = i;
      while ((newi + 1) <= (size - 1) && std::isdigit(input[newi + 1])) {
        svalue += input[newi + 1];
        newi++;
      }
      output.push_back(std::stoi(svalue));
      i = newi;
    }
  }

  return output;
}

int main() {
  std::ifstream infile("input.txt");
  std::vector<std::string> input;
  if (infile) {
    std::cout << "opened input file" << std::endl;
    std::string line;
    while (getline(infile, line)) {
      input.push_back(line);
    }
    infile.close();
  } else {
    std::cerr << "unable to open input file" << std::endl;
  }

  int sum = 0;
  int game_number = 1;
  std::vector<int> cards_won(input.size(), 1);

  for (const std::string& in : input) {
    std::string card_data = split(in, ": ")[1];
    std::vector<std::string> numbers = split(card_data, " | ");
    std::vector<int> winning_numbers = get_numbers(numbers[0]);
    std::vector<int> pulled_numbers = get_numbers(numbers[1]);

    int number_of_wins = 0;
    for (const int x : winning_numbers) {
      for (const int y : pulled_numbers) {
        if (x == y) {
          number_of_wins++;
          break;
        }
      }
    }

    for (int i = 1; i <= number_of_wins; i++) {
      cards_won[game_number - 1 + i] += cards_won[game_number - 1];
    }

    game_number++;
  }

  for (const int x : cards_won) {
    sum += x;
  }

  std::cout << sum << std::endl;

  return 0;
}
