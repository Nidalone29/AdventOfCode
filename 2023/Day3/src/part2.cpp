#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cctype>

int main() {
  std::ifstream infile("input.txt");
  if (infile) {
    std::cout << "opened input file" << std::endl;
    std::string line;
    int sum = 0;
    std::vector<std::string> input;

    while (getline(infile, line)) {
      input.push_back(line);
    }

    const int width = input[0].size();
    const int height = input.size();

    // idk why does this work? (this takes fucking 0.4MB of space)
    // TODO find a better way
    std::vector<int> stars[width][height];

    for (int i = 0; i < height; i++) {
      for (int j = 0; j < width; j++) {
        if (std::isdigit(input[i][j])) {
          std::string svalue = "";
          svalue += input[i][j];
          int newj = j;
          while (std::isdigit(input[i][newj + 1])) {
            svalue += input[i][newj + 1];
            newj++;
          }

          const int number_length = svalue.length();

          // going around the number and adding it to the star
          for (int v = -1; v < 2; v++) {
            for (int h = -1; h < number_length + 1; h++) {
              if ((i + v) < height - 1 && (i + v) >= 0 && (j + h) < width - 1 &&
                  (j + h) >= 0) {
                if (input[i + v][j + h] == '*') {
                  stars[i + v][j + h].push_back(std::stoi(svalue));
                }
              }
            }
          }

          j = newj;
        }
      }
    }

    for (int i = 0; i < height; i++) {
      for (int j = 0; j < width; j++) {
        if (stars[i][j].size() == 2) {
          sum += stars[i][j][0] * stars[i][j][1];
        }
      }
    }
    std::cout << sum << std::endl;
    std::cin.get();
    infile.close();
  } else {
    std::cerr << "unable to open input file" << std::endl;
  }
  return 0;
}