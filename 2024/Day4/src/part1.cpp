#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int main() {
  std::ifstream infile("test.txt");
  if (infile) {
    std::cout << "opened input file" << std::endl;
    std::string line;
    std::vector<std::string> input;
    int res = 0;

    while (getline(infile, line)) {
      input.push_back(line);
    }
    infile.close();

    std::string obj = "XMAS";
    std::string obj_back = "SAMX";

    // all horizontal
    for (int i = 0; i < input.size(); i++) {
      for (int j = 0; j < input[0].size() - 3; j++) {
        std::string temp = {input[i][j], input[i][j + 1], input[i][j + 2],
                            input[i][j + 3]};
        if (temp == obj || temp == obj_back) {
          res++;
        }
      }
    }

    // all vertical
    for (int i = 0; i < input[0].size(); i++) {
      for (int j = 0; j < input.size() - 3; j++) {
        std::string temp = {input[j][i], input[j + 1][i], input[j + 2][i],
                            input[j + 3][i]};
        if (temp == obj || temp == obj_back) {
          res++;
        }
      }
    }

    // top diagonal (/)
    for (int max = 3; max < input.size(); max++) {
      std::string temp;
      for (int i = 0; i <= max; i++) {
        temp += input[i][max - i];
      }
      std::cout << temp << std::endl;
    }
    std::cout << "-----------" << std::endl;

    std::cout << "-----------" << std::endl;
    // top other diagonal (\)
    for (int max = 0; max < input.size() - 3; max++) {
      std::string temp;
      for (int i = 0; i < input.size() - max; i++) {
        temp += input[i][i + max];
      }
      std::cout << temp << std::endl;
    }

    // bottom diagonal (/)
    for (int max = input.size() - 3; max >= 0; max--) {
      std::string temp;
      for (int i = 0; i <= max; i++) {
        input[i][max - i] = '.';
      }
      std::cout << temp << std::endl;
    }
    for (const auto& x : input) {
      std::cout << x << std::endl;
    }

    std::cout << res << "\n" << std::endl;

  } else {
    std::cerr << "unable to open input file" << std::endl;
  }
  return 0;
}
