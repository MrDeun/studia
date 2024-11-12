#include "LCG.h"
#include <algorithm>
#include <array>
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <map>
#include <string>
#include <vector>

#define UNREACHABLE false

using player = std::map<uint32_t, uint8_t>;

void print_state(std::vector<player> players) {
  for (auto &player : players) {
    printf("{");
    for (auto &pairs : player) {
      printf(" \"%d\" : %d,", pairs.first, pairs.second);
    }
    puts("}");
  }
}

const char *CheckThreeKind(player &player) {
  assert(player.size() == 3);
  std::array<uint8_t, 3> counts;
  int i = 0;
  for (auto &pair : player) {
    counts[i] = pair.second;
    i++;
  }

  bool threeAreSame = false;

  for (auto &count : counts) {
    if (count == 3) {
      threeAreSame = true;
    }
  }

  if (threeAreSame) {
    for (auto &count : counts) {
      if (count == 2) {
        return "Full house";
      } else {
        return "Three of a kind";
      }
    }
  } else {
    return "Two Pairs";
  }

  assert(UNREACHABLE);
}

int main() {
  LinearCongruentialGenerator gen{12857, 50000, 5421, 2341};
  const int figuresCount = 5;
  std::array<double, 10000> randomNumbers;
  for (auto &number : randomNumbers) {
    number = gen.GenerateDouble();
  }
  assert(randomNumbers[0] != randomNumbers[1]);

  std::vector<player> players(2000);
  // std::fill(players.begin(),players.end(),player_template);
  for (size_t i = 0; i < randomNumbers.size(); i++) {
    size_t current_player = i / 5;
    int figure = int(randomNumbers[i] * figuresCount);
    players[current_player][figure]++;
  }

  // print_state(players); // STATE OK

  /*
    resultCounts:
    0 - High Card
    1 - One Pair
    2 - Three Of Kind
    3 - Two Pairs
    4 - Full House
    5 - Four of a kind
    6 - Five of a kind
   */

  std::array<uint16_t, 7> resultCounts;
  std::fill(resultCounts.begin(), resultCounts.end(), 0);

  std::string res = "";
  for (auto &player : players) {
    switch (player.size()) {
    case 5:
      printf("High Card\n");
      resultCounts[0]++;
      break;
    case 4:
      printf("One Pair\n");
      resultCounts[1]++;
      break;
    case 3:
      res = CheckThreeKind(player);
      printf("%s\n", CheckThreeKind(player));
      if (res == "Full house")
        resultCounts[4]++;
      if (res == "Two Pairs")
        resultCounts[3]++;
      if (res == "Three of a kind")
        resultCounts[2]++;
      break;
    case 2:
      printf("Four of kind\n");
      resultCounts[5]++;
      break;
    case 1:
      printf("Five of a kind\n");
      resultCounts[6]++;
      break;
    default:
      assert(UNREACHABLE);
      break;
    }
    res.clear();
  }

  puts("\n\n\n\n\n\n\n");
  printf("Busts: %d\n", resultCounts[0]);
  printf("One Pairs: %d\n", resultCounts[1]);
  printf("Three of a kind: %d\n", resultCounts[2]);
  printf("Two Pairs: %d\n", resultCounts[3]);
  printf("Full Houses: %d\n", resultCounts[4]);
  printf("Four of a kind: %d\n", resultCounts[5]);
  printf("Five of a kind: %d\n", resultCounts[6]);
}