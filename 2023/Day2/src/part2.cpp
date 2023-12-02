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

    int sum = 0;
    int game_number = 1;

    while (getline(infile, line)) {
      std::vector<std::string> parsed_line = split(line, ": ");
      std::vector<std::string> matches = split(parsed_line[1], "; ");

      int max_green = -1, max_blue = -1, max_red = -1;
      std::vector<Match> match_vector;

      for (const std::string& match : matches) {
        std::vector<std::string> current_match = split(match, ", ");
        for (const std::string& cube_pull : current_match) {
          std::vector<std::string> cube_pull_values = split(cube_pull, " ");
          for (int i = 0; i < cube_pull_values.size(); i++) {
            Match curr{std::stoi(cube_pull_values[i]), cube_pull_values[i + 1]};
            match_vector.push_back(curr);
            i++;
          }
        }

        for (const Match& x : match_vector) {
          if (x.color == "green" && x.grabs > max_green) {
            max_green = x.grabs;
          } else if (x.color == "blue" && x.grabs > max_blue) {
            max_blue = x.grabs;
          } else if (x.color == "red" && x.grabs > max_red) {
            max_red = x.grabs;
          }
        }
      }
      sum += (max_blue * max_red * max_green);

      game_number++;
    }

    std::cout << sum << std::endl;
    infile.close();
  } else {
    std::cerr << "unable to open input file" << std::endl;
  }

  return 0;
}
