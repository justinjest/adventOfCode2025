#include "util.h"

#include <cstdint>
#include <cassert>
#include <iostream>
#include <vector>
#include <algorithm>

class Input {
  InputLine input;
  std::vector<bool> state;

public:
  auto pushButton (int index) {
    for (size_t i = 0; i < input.buttons[index].size(); ++i) {
      state[input.buttons[index][i]] = !state[input.buttons[index][i]];
    }
  }

  auto pushButtons (std::vector<size_t> button) {
    for (size_t j = 0; j < button.size(); ++j) {
      pushButton(button[j]);
    }
  }

  auto isSolved() {
    return state == input.truthTable;
  }

  Input() {
    InputLine input {};
    std::vector<bool> state;
  }

  Input(InputLine line) {
    input = line;
    size_t size = line.truthTable.size();
    for (size_t i = 0; i < size; ++i){
      state.push_back(false);
    }
  }

  void print() {
    input.print();
  }

  void printState() {
    for (size_t i = 0; i < state.size(); ++i) {
      std::cout << (state[i] ? '#' : '.');
    }
    std::cout << '\n';
  }

  auto smallestSolve() {
    std::vector<bool> empty(state.size(), false); // This needs to be done better

    for (size_t ones = 1; ones <= state.size(); ++ones) {
      std::vector<int> perms(state.size(), 0);
      std::fill(perms.end() - ones- 1, perms.end() - 1, 1);

      do {
        state = empty;

        for (size_t i = 0; i < perms.size(); i++) {
          //std::cout << i << " Perms being checked\n";
          if (perms[i])
            pushButton(i);
        }

        if (isSolved()){
          int sum {0};
          for (size_t i = 0; i < perms.size(); ++i) {
            sum += perms[i];
          }
          std::cout << "Finished with " << sum << " button presses" << '\n';
          return;
          }
      }
      while(std::next_permutation(perms.begin(), perms.end()));
    }
  }

  auto chatGPTSmallestSolve() {
    const size_t n = input.buttons.size();
    std::vector<bool> empty(state.size(), false);

    for (size_t presses = 1; presses <= n; ++presses) {
        uint64_t mask = (1ULL << presses) - 1;   // 000...0111

        const uint64_t limit = 1ULL << n;

        while (mask < limit) {
            state = empty;

            for (size_t i = 0; i < n; ++i) {
                if (mask & (1ULL << i))
                    pushButton(i);
            }

            if (isSolved()) {
                std::cout << "Finished with "
                          << presses
                          << " button presses\n";
                return presses;
            }

            // next combination with same number of bits
            uint64_t c = mask & -mask;
            uint64_t r = mask + c;
            mask = (((r ^ mask) >> 2) / c) | r;
        }
    }
    return static_cast<uint64_t>(0);
    }
};


auto main() -> int {


  std::vector<InputLine> data {processFile("input10.txt")};
  uint64_t val {0};
  for (size_t i = 0; i < data.size(); ++i) {
    Input d {data[i]};
    d.print();
    uint64_t temp = d.chatGPTSmallestSolve();
    assert(temp != 0);
    val += temp;
  }
  std::cout << "Minimum button presses " << val << "\n";
  return 0;
}
