#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>

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

long long get_number(const std::string& input) {
  const int size = input.length();

  std::string svalue = "";
  for (int i = 0; i < size; i++) {
    if (std::isdigit(input[i])) {
      svalue += input[i];
    }
  }

  return std::stoll(svalue);
}

int main() {
  std::ifstream infile("input.txt");
  std::vector<std::string> input;

  if (infile) {
    std::cout << "opened input file" << std::endl;

    std::string line;
    while (getline(infile, line)) {
      input.push_back(line);
    }

    infile.close();
  } else {
    std::cerr << "unable to open input file" << std::endl;
  }

  const long long max_time = get_number(split(input[0], ":")[1]);
  const long long record_distance = get_number(split(input[1], ":")[1]);

  long long res = 1;

  // found using desmos
  // y= -x^2 + current_race.max_time*x - current_race.record_distance
  const long long a = -1;
  const long long b = max_time;
  const float c = -record_distance - .1F;  // beating distance
  // find solutions using quadratic formula
  long long delta = std::pow(b, 2) - 4 * a * c;
  if (delta > 0) {
    // two solutions
    long long sol_left = std::ceil((-b + std::sqrt(delta)) / (2 * a));
    long long sol_right = std::floor((-b - std::sqrt(delta)) / (2 * a));
    res *= sol_right - sol_left + 1;
  } else if (delta == 0) {
    // one solution (i don't think this is needed)
    long long sol = std::floor((-b + std::sqrt(delta)) / (2 * a));
    std::cout << sol << '\n';
    res *= sol;
  } else {
    // no solutions (you can't beat the record)
  }

  std::cout << res << std::endl;

  return 0;
}
