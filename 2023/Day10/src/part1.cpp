#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <utility>

struct Node {
  Node(const int& d, const char& p) : distance(d), pipe_type(p) {}
  Node() : distance(INT_MAX), pipe_type('#') {}
  int distance;
  char pipe_type;
};

using Coords = std::pair<int, int>;
using NodeCoords = std::pair<Node, Coords>;
using Map = std::vector<std::vector<Node>>;

bool possible_north(const Node& input) {
  return (input.pipe_type == '|' || input.pipe_type == '7' ||
          input.pipe_type == 'F');
}

bool possible_south(const Node& input) {
  return (input.pipe_type == '|' || input.pipe_type == 'L' ||
          input.pipe_type == 'J');
}

bool possible_east(const Node& input) {
  return (input.pipe_type == '-' || input.pipe_type == '7' ||
          input.pipe_type == 'J');
}

bool possible_west(const Node& input) {
  return (input.pipe_type == '-' || input.pipe_type == 'F' ||
          input.pipe_type == 'L');
}

/**
 * @brief updates the map after it had been visited using bfs from 'S'
 *
 * @param start
 * @param map
 */
void bfs(const NodeCoords& start, Map& map) {
  map[start.second.first][start.second.second].distance = 0;
  std::queue<NodeCoords> q;
  q.push(start);
  while (!q.empty()) {
    NodeCoords current = q.front();
    q.pop();
    const int curr_i = current.second.first;
    const int curr_j = current.second.second;

    // north
    if (curr_i - 1 >= 0) {
      if (possible_north(map[curr_i - 1][curr_j]) &&
          map[curr_i - 1][curr_j].distance == INT_MAX) {
        map[curr_i - 1][curr_j].distance = map[curr_i][curr_j].distance + 1;
        q.push({map[curr_i - 1][curr_j], {curr_i - 1, curr_j}});
      }
    }
    // south
    if (curr_i + 1 <= map.size() - 1) {
      if (possible_south(map[curr_i + 1][curr_j]) &&
          map[curr_i + 1][curr_j].distance == INT_MAX) {
        map[curr_i + 1][curr_j].distance = map[curr_i][curr_j].distance + 1;
        q.push({map[curr_i + 1][curr_j], {curr_i + 1, curr_j}});
      }
    }
    // east
    if (curr_j + 1 <= map[0].size() - 1) {
      if (possible_east(map[curr_i][curr_j + 1]) &&
          map[curr_i][curr_j + 1].distance == INT_MAX) {
        map[curr_i][curr_j + 1].distance = map[curr_i][curr_j].distance + 1;
        q.push({map[curr_i][curr_j + 1], {curr_i, curr_j + 1}});
      }
    }
    // west
    if (curr_j - 1 >= 0) {
      if (possible_west(map[curr_i][curr_j - 1]) &&
          map[curr_i][curr_j - 1].distance == INT_MAX) {
        map[curr_i][curr_j - 1].distance = map[curr_i][curr_j].distance + 1;
        q.push({map[curr_i][curr_j - 1], {curr_i, curr_j - 1}});
      }
    }
  }
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

  Map map;
  NodeCoords start;

  for (int i = 0; i < input.size(); i++) {
    std::vector<Node> temp;
    for (int j = 0; j < input[i].size(); j++) {
      temp.emplace_back(INT_MAX, input[i][j]);
      if (input[i][j] == 'S') {
        start.first = {0, 'S'};
        start.second = {i, j};
      }
    }
    map.emplace_back(temp);
  }

  bfs(start, map);

  int max = -1;

  for (int i = 0; i < map.size(); i++) {
    for (int j = 0; j < map[i].size(); j++) {
      if (map[i][j].distance > max && map[i][j].distance != INT_MAX) {
        max = map[i][j].distance;
      }
    }
  }

  std::cout << max << std::endl;
  return 0;
}
