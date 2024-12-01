#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

int main() {
  std::ifstream infile("input.txt");
  if (infile) {
    std::cout << "opened input file" << std::endl;
    std::string line;
    int sum = 0;
    std::vector<int> left;
    std::vector<int> right;
    while (getline(infile, line)) {
      std::string a;
      int i = 0;
      while (line[i] != ' ') {
        a += line[i];
        i++;
      }
      left.push_back(std::stoi(a));
      right.push_back(std::stoi(line.substr(i)));
    }

    std::sort(left.begin(), left.end());
    std::sort(right.begin(), right.end());

    for (int i = 0; i < left.size(); i++) {
      sum += std::abs(left[i] - right[i]);
    }

    std::cout << sum << std::endl;
    infile.close();
  } else {
    std::cerr << "unable to open input file" << std::endl;
  }
  return 0;
}
