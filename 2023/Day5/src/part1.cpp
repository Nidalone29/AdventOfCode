#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <sstream>
#include <algorithm>

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

std::vector<long long> get_numbers(const std::string& input) {
  std::vector<long long> output;
  const int size = input.length();

  for (int i = 0; i < size; i++) {
    if (std::isdigit(input[i])) {
      std::string svalue = "";
      svalue += input[i];
      int newi = i;
      while ((newi + 1) <= (size - 1) && std::isdigit(input[newi + 1])) {
        svalue += input[newi + 1];
        newi++;
      }
      output.push_back(std::stoll(svalue));
      i = newi;
    }
  }

  return output;
}

int main() {
  std::ifstream infile("input.txt");

  std::vector<std::string> separated_inputs;

  if (infile) {
    std::cout << "opened input file" << std::endl;
    std::string line;
    std::string input;
    while (getline(infile, line)) {
      if (line == "") {
        separated_inputs.push_back(input);
        input.clear();
      } else {
        input += (line) + '\n';
      }
    }
    separated_inputs.push_back(input);

    infile.close();
  } else {
    std::cerr << "unable to open input file" << std::endl;
  }

  // get seeds
  std::vector<std::string> seeds_line = split(separated_inputs[0], ": ");

  std::vector<long long> seeds = get_numbers(seeds_line[1]);

  // index 0 => to_soil, 1 => to_fert...
  // it contains arrays of [dst  start, src range start, range]
  std::array<std::vector<std::array<long long, 3>>, 7> maps;

  for (int i = 1; i < separated_inputs.size(); i++) {
    std::vector<std::string> current_map = split(separated_inputs[i], "\n");
    for (int j = 1; j < current_map.size() - 1; j++) {
      std::vector<long long> x = get_numbers(current_map[j]);
      std::array<long long, 3> temp;
      std::copy(x.begin(), x.end(), temp.begin());
      maps[i - 1].push_back(temp);
    }
  }

  for (std::vector<std::array<long long, 3>> x : maps) {
    std::sort(x.begin(), x.end(),
              [](std::array<long long, 3> a, std::array<long long, 3> b) {
                return a[1] < b[1];
              });
  }

  for (long long& seed : seeds) {
    for (const std::vector<std::array<long long, 3>>& x : maps) {
      bool found = false;
      for (const std::array<long long, 3>& y : x) {
        if (!found && seed >= y[1] && seed <= y[1] + y[2] - 1) {
          seed += y[0] - y[1];
          found = true;
        }
      }
    }
  }

  std::cout << *std::min_element(seeds.begin(), seeds.end()) << std::endl;

  return 0;
}
