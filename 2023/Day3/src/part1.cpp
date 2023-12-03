#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cctype>

bool check_around(const std::vector<std::string>& input, const int i,
                  const int j, const int number_length, const int width,
                  const int height) {
  for (int v = -1; v < 2; v++) {
    for (int h = -1; h < number_length + 1; h++) {
      if ((i + v) < height - 1 && (i + v) >= 0 && (j + h) < width - 1 &&
          (j + h) >= 0) {
        if (!std::isdigit(input[i + v][j + h]) && input[i + v][j + h] != '.') {
          return true;
        }
      }
    }
  }
  return false;
}

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

    const int height = input.size();
    const int width = input[0].size();

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

          if (check_around(input, i, j, number_length, width, height)) {
            sum += std::stoi(svalue);
          }

          j = newj;
        }
      }
    }

    std::cout << sum << std::endl;
    infile.close();
  } else {
    std::cerr << "unable to open input file" << std::endl;
  }
  return 0;
}