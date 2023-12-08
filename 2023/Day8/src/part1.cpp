#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>

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

  std::string start = "AAA";
  int step_counter = 0;
  int path_iter = 0;
  while (start != "ZZZ") {
    if (path_iter == path.size()) {
      path_iter = 0;
    }
    if (path[path_iter] == 'L') {
      start = map[start].first;
    } else {  // == 'R'
      start = map[start].second;
    }
    step_counter++;
    path_iter++;
  }

  std::cout << step_counter << std::endl;
  return 0;
}
