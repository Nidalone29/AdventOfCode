#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int main() {
  std::ifstream infile("input.txt");
  if (infile) {
    std::cout << "opened input file" << std::endl;
    std::string line;
    std::string input;
    int res = 0;

    while (getline(infile, line)) {
      input += line;
    }
    infile.close();

    std::cout << res << "\n" << std::endl;

  } else {
    std::cerr << "unable to open input file" << std::endl;
  }
  return 0;
}
