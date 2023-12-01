#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>

int main() {
  std::ifstream infile("input.txt");
  if (infile) {
    std::cout << "opened input file" << std::endl;
    std::string line;
    int sum = 0;
    std::map<std::string, char> number_letters = {
        {"zero", '0'},  {"one", '1'},  {"two", '2'}, {"three", '3'},
        {"four", '4'},  {"five", '5'}, {"six", '6'}, {"seven", '7'},
        {"eight", '8'}, {"nine", '9'}};
    std::vector<char> possible_digits = {'0', '1', '2', '3', '4',
                                         '5', '6', '7', '8', '9'};
    while (getline(infile, line)) {
      std::string::size_type first_digit = std::string::npos, last_digit = 0;

      for (char x : possible_digits) {
        if (line.find(x) != std::string::npos && first_digit > line.find(x)) {
          first_digit = line.find(x);
        }
        if (line.rfind(x) != std::string::npos && last_digit < line.rfind(x)) {
          last_digit = line.rfind(x);
        }
      }

      std::string first_value = "";
      first_value += line[first_digit];
      std::string second_value = "";
      second_value += line[last_digit];

      for (const auto& [letters, value] : number_letters) {
        if (line.find(letters) != std::string::npos &&
            first_digit > line.find(letters)) {
          first_digit = line.find(letters);
          first_value = value;
        }
        if (line.rfind(letters) != std::string::npos &&
            last_digit < line.rfind(letters)) {
          last_digit = line.rfind(letters);
          second_value = value;
        }
      }

      std::string svalue = "";
      svalue += first_value;
      svalue += second_value;

      sum += std::stoi(svalue);
    }

    std::cout << sum << std::endl;
    infile.close();
  } else {
    std::cerr << "unable to open input file" << std::endl;
  }
  return 0;
}