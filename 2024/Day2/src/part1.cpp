#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int main() {
  std::ifstream infile("input.txt");
  if (infile) {
    std::cout << "opened input file" << std::endl;
    std::string line;
    int res = 0;
    while (getline(infile, line)) {
      std::vector<int> reports;
      std::string temp;
      for (int i = 0; i < line.size(); i++) {
        if (line[i] == ' ') {
          reports.push_back(std::stoi(temp));
          temp = "";
        } else {
          temp += line[i];
        }
      }
      reports.push_back(std::stoi(temp));

      const bool is_increasing = (reports[0] < reports[1]);
      bool is_safe = true;
      for (int i = 0; i < reports.size() - 1; i++) {
        if (is_increasing && reports[i] > reports[i + 1]) {
          is_safe = false;
        }
        if (!is_increasing && reports[i] < reports[i + 1]) {
          is_safe = false;
        }
        if (std::abs(reports[i] - reports[i + 1]) < 1 ||
            std::abs(reports[i] - reports[i + 1]) > 3) {
          is_safe = false;
        }
        if (reports[i] == reports[i + 1]) {
          is_safe = false;
        }
      }

      if (is_safe) {
        res++;
      }
    }

    std::cout << res << "\n" << std::endl;
    infile.close();
  } else {
    std::cerr << "unable to open input file" << std::endl;
  }
  return 0;
}
