#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>

int main() {
  std::ifstream infile("input.txt");
  if (infile) {
    std::cout << "opened input file" << std::endl;
    std::string line;
    std::string input;
    int res = 0;
    std::regex regex_mul(R"(mul\(([\d]*),([\d]*)\))");

    while (getline(infile, line)) {
      input += line;
    }
    infile.close();

    for (std::smatch sm; std::regex_search(input, sm, regex_mul);) {
      res += std::stoi(sm[1]) * std::stoi(sm[2]);
      input = sm.suffix();
    }

    std::cout << res << "\n" << std::endl;

  } else {
    std::cerr << "unable to open input file" << std::endl;
  }
  return 0;
}
