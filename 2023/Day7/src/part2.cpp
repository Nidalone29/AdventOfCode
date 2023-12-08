#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <array>
#include <algorithm>

std::map<char, int> strength = {
    {'A', 12}, {'K', 11}, {'Q', 10}, {'T', 9}, {'9', 8}, {'8', 7}, {'7', 6},
    {'6', 5},  {'5', 4},  {'4', 3},  {'3', 2}, {'2', 1}, {'J', 0}};

// already sorted
enum HAND_TYPE {
  HIGH_CARD,
  ONE_PAIR,
  TWO_PAIR,
  THREE_OF_A_KIND,
  FULL_HOUSE,
  FOUR_OF_A_KIND,
  FIVE_OF_A_KIND
};

class Hand {
 public:
  Hand(const std::string hand) {
    if (hand.size() != 5) {
      std::cerr << "error creating hand" << std::endl;
      throw;
    }
    for (int i = 0; i < hand.size(); i++) {
      _cards[i] = hand[i];
    }
    find_type();
  }

  const std::array<char, 5>& getCards() const {
    return _cards;
  }

  const HAND_TYPE& getType() const {
    return _type;
  }

  friend bool operator<(const Hand& l, const Hand& r) {
    if (l._type < r._type) {
      return true;
    } else if (l._type > r._type) {
      return false;
    } else {  // l._type == r._type
      for (int i = 0; i < l._cards.size();) {
        if (strength[l._cards[i]] == strength[r._cards[i]]) {
          i++;
        } else if (strength[l._cards[i]] < strength[r._cards[i]]) {
          return true;
        } else {
          return false;
        }
      }
    }
  }

  friend bool operator>(const Hand& l, const Hand& r) {
    return r < l;
  }

  friend bool operator<=(const Hand& l, const Hand& r) {
    return !(l > r);
  }

  friend bool operator>=(const Hand& l, const Hand& r) {
    return !(l < r);
  }

 private:
  void find_type() {
    std::map<char, int> cards_count;
    for (const char x : _cards) {
      const auto [_, success] = cards_count.insert({x, 1});
      if (!success) {
        cards_count[x]++;
      }
    }

    // find the card with the highest count and add the numbers of J
    if (cards_count.find('J') != cards_count.end()) {
      int max_count = -1;
      char max_card;
      for (const auto [card, count] : cards_count) {
        if (count > max_count && card != 'J') {
          max_count = count;
          max_card = card;
        }
      }
      cards_count[max_card] += cards_count['J'];
      cards_count.erase('J');
    }

    if (cards_count.size() == 1) {
      _type = HAND_TYPE::FIVE_OF_A_KIND;
    } else if (cards_count.size() == 2) {
      for (const auto& [name, count] : cards_count) {
        if (count == 1 || count == 4) {
          _type = HAND_TYPE::FOUR_OF_A_KIND;
          break;
        } else {
          _type = HAND_TYPE::FULL_HOUSE;
          break;
        }
      }
    } else if (cards_count.size() == 3) {
      bool found_3 = false;
      for (const auto& [name, count] : cards_count) {
        if (count == 3) {
          _type = HAND_TYPE::THREE_OF_A_KIND;
          found_3 = true;
          break;
        }
      }
      if (!found_3) {
        _type = HAND_TYPE::TWO_PAIR;
      }
    } else if (cards_count.size() == 4) {
      _type = HAND_TYPE::ONE_PAIR;
    } else if (cards_count.size() == 5) {
      _type = HAND_TYPE::HIGH_CARD;
    }
  }

  std::array<char, 5> _cards;

  HAND_TYPE _type;
};

std::ostream& operator<<(std::ostream& stream, const Hand& other) {
  stream << "type  " << other.getType() << "| cards "
         << other.getCards().data();
  return stream;
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

int main() {
  std::ifstream infile("input.txt");
  std::vector<std::string> input;
  // hand and bidding amount
  std::vector<std::pair<Hand, int>> set_of_hands;

  if (infile) {
    std::cout << "opened input file" << std::endl;
    std::string line;

    while (getline(infile, line)) {
      std::vector<std::string> splitted_line = split(line, " ");
      set_of_hands.push_back(
          {Hand(splitted_line[0]), std::stoi(splitted_line[1])});
    }

    infile.close();
  } else {
    std::cerr << "unable to open input file" << std::endl;
  }

  std::sort(set_of_hands.begin(), set_of_hands.end(),
            [](std::pair<Hand, int> a, std::pair<Hand, int> b) {
              return a.first < b.first;
            });

  int res = 0;
  for (int i = 1; i <= set_of_hands.size(); i++) {
    res += set_of_hands[i - 1].second * i;
  }

  std::cout << res << std::endl;
  return 0;
}
