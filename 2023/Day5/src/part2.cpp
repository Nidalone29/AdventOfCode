#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <sstream>
#include <algorithm>
#include <map>
#include <utility>

// TODO clean up because it's trash

using long64 = long long;

// start and end of range (all inclusive)
using Range = std::pair<long64, long64>;
// all the ranges in a map
// first range is source, second range is destination
using RangeMapping = std::pair<Range, Range>;
using Mappings = std::vector<RangeMapping>;

Range getRange(const long64 src_start, const long64 range_size) {
  return {src_start, src_start + range_size - 1};
}

RangeMapping getRangeMapping(const long64 src_start, const long64 dst_start,
                             const long64 range_size) {
  return {getRange(src_start, range_size), getRange(dst_start, range_size)};
}

std::ostream& operator<<(std::ostream& stream, const Range& x) {
  stream << "[" << x.first << ", " << x.second << "]";
  return stream;
}

std::ostream& operator<<(std::ostream& stream, const RangeMapping& x) {
  stream << x.first << " => " << x.second;
  return stream;
}

std::vector<Range> applyMap(Range input, const Mappings& current_map) {
  // completely outside of the sorted mappings
  if (input.second < current_map[0].first.first ||
      input.first > current_map[current_map.size() - 1].first.second) {
    return {input};
  }

  std::vector<Range> output = {};
  if (input.first < current_map[0].first.first &&
      input.second >= current_map[0].first.first) {
    output.push_back({input.first, current_map[0].first.first - 1});
    input = {current_map[0].first.first, input.second};
  }

  // actual logic when in the middle
  for (int i = 0; i < current_map.size(); i++) {
    Range src = current_map[i].first;
    long64 offset = current_map[i].second.first - current_map[i].first.first;

    if (input.first >= src.first && input.first <= src.second) {
      // completely inside
      if (input.second <= src.second) {
        output.push_back({input.first + offset, input.second + offset});
      }
      // have to split because the end is "overflowing"
      else {
        // end overflew on another range
        if (input.second <= current_map[current_map.size() - 1].first.second) {
          output.push_back(
              {input.first + offset, current_map[i].second.second});
          input = {src.second + 1, input.second};
        }
        // end overflew outside
        else {
          output.push_back({src.second + 1, input.second});
        }
      }
    }
  }
  // one range, or more ranges (splitted)
  return output;
}

// apply the maps to the seed
std::vector<Range> applyMaps(const Range& input,
                             const std::array<Mappings, 7>& all_maps) {
  std::vector<Range> output = applyMap(input, all_maps[0]);

  for (int i = 1; i < all_maps.size(); i++) {
    std::vector<Range> res;
    for (const Range& x : output) {
      std::vector<Range> temp = applyMap(x, all_maps[i]);
      res.insert(res.end(), temp.begin(), temp.end());
    }
    output = res;
  }

  return output;
}

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

std::vector<long64> get_numbers(const std::string& input) {
  std::vector<long64> output;
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
  std::vector<long64> seeds = get_numbers(seeds_line[1]);
  std::vector<Range> seed_ranges;
  for (int i = 0; i < seeds.size(); i++) {
    seed_ranges.push_back({seeds[i], seeds[i] + seeds[i + 1] - 1});
    i++;
  }

  // index 0 => to_soil, 1 => to_fert...
  // it contains arrays of [dst start, src range start, range]
  std::array<Mappings, 7> maps;

  // get the maps
  for (int i = 1; i < separated_inputs.size(); i++) {
    std::vector<std::string> current_map = split(separated_inputs[i], "\n");

    // skipping the first line "x-to-x map:" (and until size-1 because of end
    // empty line)
    for (int j = 1; j < current_map.size() - 1; j++) {
      std::vector<long64> mapping_numbers = get_numbers(current_map[j]);
      maps[i - 1].push_back(getRangeMapping(
          mapping_numbers[1], mapping_numbers[0], mapping_numbers[2]));
    }
  }

  for (Mappings& current_map : maps) {
    // sort by source for convinience
    std::sort(current_map.begin(), current_map.end(),
              [](const RangeMapping a, const RangeMapping b) {
                return a.first.first < b.first.first;
              });
  }

  // nasty empty edge case
  // |----|   |------|
  for (Mappings& current_map : maps) {
    for (int i = 0; i < current_map.size() - 1; i++) {
      if (current_map[i].first.second + 1 != current_map[i + 1].first.first) {
        current_map.insert(current_map.begin() + i + 1,
                           {{current_map[i].first.second + 1,
                             current_map[i + 1].first.first - 1},
                            {current_map[i].first.second + 1,
                             current_map[i + 1].first.first - 1}});
        i++;
      }
    }
  }

  // now we now that all the mapping are contiguous
  std::vector<Range> processed_seeds;
  for (const Range& seed_range : seed_ranges) {
    std::vector<Range> seed_output = applyMaps(seed_range, maps);
    processed_seeds.insert(processed_seeds.end(), seed_output.begin(),
                           seed_output.end());
  }

  std::sort(processed_seeds.begin(), processed_seeds.end(),
            [](const Range a, const Range b) { return a.first < b.first; });

  // the lowest seed location
  std::cout << processed_seeds[0].first << std::endl;

  return 0;
}
