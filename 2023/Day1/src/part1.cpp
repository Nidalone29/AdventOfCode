#include <fstream>
#include <iostream>
#include <string>

int main() {
  std::ifstream infile("input.txt");
  if (infile) {
    std::cout << "opened input file" << std::endl;
    std::string line;
    int sum = 0;
    while (getline(infile, line)) {
      std::string::size_type first_digit, last_digit;
      first_digit = line.find_first_of("0123456789");
      last_digit = line.find_last_of("0123456789");
      std::string svalue = "";
      svalue += line[first_digit];
      svalue += line[last_digit];
      sum += std::stoi(svalue);
    }

    std::cout << sum << std::endl;
    infile.close();
  } else {
    std::cerr << "unable to open input file" << std::endl;
  }
  return 0;
}