#include <fstream>
#include <iostream>
#include <string>
#include <vector>

/**
 * @brief splitting a string by a substring and returning a vector of strings
 * containing all parts (Note that there will be no occurrences of the substring
 * that is used to split)
 *
 * @param input
 * @param x
 * @return std::vector<std::string>
 */
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

// a Game is a collection of Matches
struct Match {
  int grabs;
  std::string color;
};

int main() {
  std::ifstream infile("input.txt");
  if (infile) {
    std::cout << "opened input file" << std::endl;
    std::string line;

    const int max_red = 12;
    const int max_green = 13;
    const int max_blue = 14;
    int sum = 0;
    int game_number = 1;

    while (getline(infile, line)) {
      bool valid_game = true;
      std::vector<std::string> parsed_line = split(line, ": ");
      std::vector<std::string> matches = split(parsed_line[1], "; ");

      for (const std::string& match : matches) {
        std::vector<std::string> current_match = split(match, ", ");
        for (const std::string& cube_pull : current_match) {
          std::vector<std::string> cube_pull_values = split(cube_pull, " ");
          for (int i = 0; i < cube_pull_values.size(); i++) {
            Match curr{std::stoi(cube_pull_values[i]), cube_pull_values[i + 1]};
            if (curr.color == "green" && curr.grabs > max_green) {
              valid_game = false;
            } else if (curr.color == "blue" && curr.grabs > max_blue) {
              valid_game = false;
            } else if (curr.color == "red" && curr.grabs > max_red) {
              valid_game = false;
            }
            i++;
          }
        }
      }

      if (valid_game) {
        sum += game_number;
      }

      game_number++;
    }

    std::cout << sum << std::endl;
    infile.close();
  } else {
    std::cerr << "unable to open input file" << std::endl;
  }

  return 0;
}
