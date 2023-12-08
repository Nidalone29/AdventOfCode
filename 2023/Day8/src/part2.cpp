#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cmath>

// NOTE: mcm = minimo comune multiplo = least common multiple
// https://en.wikipedia.org/wiki/Least_common_multiple
// NOTE: MCD = Massimo comun divisore = Greatest common divisor
// https://en.wikipedia.org/wiki/Greatest_common_divisor

/**
 * @brief return the Greatest common divisor(a, b) using the euclidean algorithm
 * https://en.wikipedia.org/wiki/Euclidean_algorithm
 *
 */
long long GCD(const long long a, const long long b) {
  if (b == 0) {
    return a;
  }
  long long r = a % b;
  if (r == 0) {
    return b;
  } else {
    return GCD(b, r);
  }
}

/**
 * @brief returns the Least common multiple(a, b) using the greatest common
 * divisor
 * https://en.wikipedia.org/wiki/Least_common_multiple#Calculation
 *
 */
long long lcm(const long long a, const long long b) {
  if (a == 0 && b == 0) {
    return 0;
  }
  // the result of the division is alwaysa an integer
  return std::abs(a) * (std::abs(b) / GCD(a, b));
}

/**
 * @brief compute the least common multiple of a series of numbers
 *
 */
long long lcm_n(const std::vector<long long>& numbers) {
  long long lcm_ab = lcm(numbers[0], numbers[1]);
  if (numbers.size() == 2) {
    return lcm_ab;
  } else {
    std::vector<long long> res;
    res.push_back(lcm_ab);
    res.insert(res.end(), numbers.begin() + 2, numbers.end());
    return lcm_n(res);
  }
}

int main() {
  std::ifstream infile("input.txt");
  std::vector<std::string> input;
  std::map<std::string, std::pair<std::string, std::string>> map;

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

  const std::string path = input[0];

  for (int i = 2; i < input.size(); i++) {
    // i'm lazy
    std::string current = "";
    current += input[i][0];
    current += input[i][1];
    current += input[i][2];
    std::string left = "";
    left += input[i][7];
    left += input[i][8];
    left += input[i][9];
    std::string right = "";
    right += input[i][12];
    right += input[i][13];
    right += input[i][14];

    map.insert({current, {left, right}});
  }

  // node and number of steps used
  std::vector<std::pair<std::string, int>> starting_nodes;
  for (const auto& [current, _] : map) {
    if (current[2] == 'A') {
      starting_nodes.push_back({current, 0});
    }
  }

  for (int i = 0; i < starting_nodes.size(); i++) {
    int path_iter = 0;

    while (starting_nodes[i].first[2] != 'Z') {
      if (path_iter == path.size()) {
        path_iter = 0;
      }
      // make a step
      if (path[path_iter] == 'L') {
        starting_nodes[i].first = map[starting_nodes[i].first].first;
      } else {  // == 'R'
        starting_nodes[i].first = map[starting_nodes[i].first].second;
      }
      starting_nodes[i].second++;
      path_iter++;
    }
  }

  std::vector<long long> winning_paths;
  for (const auto& [_, steps_to_win] : starting_nodes) {
    winning_paths.push_back(steps_to_win);
  }

  long long winning_steps = lcm_n(winning_paths);
  std::cout << winning_steps << std::endl;
  return 0;
}
