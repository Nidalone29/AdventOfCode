#include <fstream>
#include <iostream>
#include <string>
#include <vector>

std::vector<int> split_numbers(const std::string& input, const std::string x) {
  std::vector<int> output;
  std::string to_tokenize = input;

  while (to_tokenize.find(x) != std::string::npos) {
    output.push_back(std::stoi(to_tokenize.substr(0, to_tokenize.find(x))));
    to_tokenize = to_tokenize.substr(to_tokenize.find(x) + x.size());
  }
  output.push_back(std::stoi(to_tokenize));

  return output;
}

std::vector<int> compute_differences(const std::vector<int>& input) {
  std::vector<int> output;
  for (int i = 0; i < input.size() - 1; i++) {
    output.push_back(input[i + 1] - input[i]);
  }
  return output;
}

bool check_zeors(const std::vector<int>& input) {
  for (const int x : input) {
    if (x != 0) {
      return false;
    }
  }
  return true;
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

  int sum = 0;
  for (const std::string& x : input) {
    std::vector<std::vector<int>> differences;
    std::vector<int> current_numbers = split_numbers(x, " ");
    differences.push_back(current_numbers);
    while (!check_zeors(differences[differences.size() - 1])) {
      differences.push_back(
          compute_differences(differences[differences.size() - 1]));
    }

    // it's just the sum
    int current_sum = 0;
    for (const std::vector<int>& row : differences) {
      current_sum += row[row.size() - 1];
    }
    sum += current_sum;
  }

  std::cout << sum << std::endl;

  return 0;
}
