#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>

int main() {
  std::ifstream infile("input.txt");
  if (infile) {
    std::cout << "opened input file" << std::endl;
    std::string line;
    int similarity_score = 0;
    std::vector<int> left;
    std::unordered_map<int, int> right;
    while (getline(infile, line)) {
      std::string a;
      int i = 0;
      while (line[i] != ' ') {
        a += line[i];
        i++;
      }
      left.push_back(std::stoi(a));
      right[std::stoi(line.substr(i))]++;
    }

    for (int i = 0; i < left.size(); i++) {
      similarity_score += left[i] * right[left[i]];
    }

    std::cout << similarity_score << std::endl;
    infile.close();
  } else {
    std::cerr << "unable to open input file" << std::endl;
  }
  return 0;
}
