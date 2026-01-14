#include "util.h"

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
    std::vector<bool> empty = state; // This needs to be done better
    std::vector<int> perms(state.size(), 0);
    perms.back() = 1;
    int breakOut {0};
    while (!isSolved() || breakOut <= 10){
      std::cout << "new state\n";
      state = empty;
      for (size_t i = 0; i < perms.size(); ++i) {
        if (perms[i] == 1)
          pushButton(i);
        if(isSolved()) return;
      }
      printState();
      std::next_permutation(perms.begin(), perms.end());
    }
    breakOut++;
  }

};



auto main() -> int {


  std::vector<InputLine> data {processFile("example.txt")};
  for (size_t i = 0; i < data.size(); i++) {
    Input d {data[i]};
    d.print();
    d.printState();
    d.smallestSolve();
  }
  return 0;
}
