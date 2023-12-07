#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>

struct Race {
  int max_time;         // in ms
  int record_distance;  // in mm
};

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

std::vector<int> get_numbers(const std::string& input) {
  std::vector<int> output;
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
      output.push_back(std::stoi(svalue));
      i = newi;
    }
  }

  return output;
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

  std::vector<Race> races;
  const std::vector<int> races_ms_values = get_numbers(split(input[0], ":")[1]);
  const std::vector<int> races_ds_values = get_numbers(split(input[1], ":")[1]);
  if (races_ms_values.size() != races_ds_values.size()) {
    std::cerr << "error parsing input" << std::endl;
    std::cout << races_ms_values.size() << " != " << races_ds_values.size()
              << std::endl;
    return -1;
  }

  for (int i = 0; i < races_ms_values.size(); i++) {
    races.push_back({races_ms_values[i], races_ds_values[i]});
  }

  int res = 1;
  for (const Race& current_race : races) {
    // found using desmos
    // y= -x^2 + current_race.max_time*x - current_race.record_distance
    const int a = -1;
    const int b = current_race.max_time;
    const float c = -current_race.record_distance - .1F;  // beating distance
    // find solutions using quadratic formula
    int delta = std::pow(b, 2) - 4 * a * c;
    if (delta > 0) {
      // two solutions
      int sol_left = std::ceil((-b + std::sqrt(delta)) / (2 * a));
      int sol_right = std::floor((-b - std::sqrt(delta)) / (2 * a));
      res *= sol_right - sol_left + 1;
    } else if (delta == 0) {
      // one solution (i don't think this is needed)
      int sol = std::floor((-b + std::sqrt(delta)) / (2 * a));
      std::cout << sol << '\n';
      res *= sol;
    } else {
      // no solutions (you can't beat the record)
    }
  }

  std::cout << res << std::endl;

  return 0;
}
