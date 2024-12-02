#include <iostream>
#include <fstream>
#include <string>
#include <vector>

// this is a shame, a disgrace

bool expected_val(const int val, const int other, const bool is_inc) {
  if (is_inc) {
    if (other >= val + 1 && other <= val + 3) {
      return true;
    }
  } else {
    if (other <= val - 1 && other >= val - 3) {
      return true;
    }
  }
  return false;
}

bool is_report_good(const std::vector<int>& rep, const bool is_inc) {
  for (int i = 0; i < rep.size() - 1; i++) {
    if (!expected_val(rep[i], rep[i + 1], is_inc)) {
      return false;
    }
  }
  return true;
}

int main() {
  std::ifstream infile("input.txt");
  if (infile) {
    std::cout << "opened input file" << std::endl;
    std::string line;
    int res = 0;
    std::vector<std::vector<int>> unsafes;

    while (getline(infile, line)) {
      std::vector<int> reports;
      std::string temp;
      for (int i = 0; i < line.size(); i++) {
        if (line[i] == ' ') {
          reports.push_back(std::stoi(temp));
          temp = "";
        } else {
          temp += line[i];
        }
      }
      reports.push_back(std::stoi(temp));

      const bool is_increasing = (reports[0] < reports[reports.size() - 1]);
      if (is_report_good(reports, is_increasing)) {
        res++;
      } else {
        int counter = 0;
        bool found = false;
        for (int i = 0; i < reports.size(); i++) {
          std::vector<int> temp = reports;
          temp.erase(temp.begin() + i);
          if (is_report_good(temp, is_increasing)) {
            found = true;
          }
        }
        if (found) {
          res++;
        }
      }
    }

    infile.close();

    std::cout << std::endl;
    std::cout << res << "\n" << std::endl;

  } else {
    std::cerr << "unable to open input file" << std::endl;
  }
  return 0;
}
