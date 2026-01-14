#include "util.h"

#include <fstream>
#include <vector>
#include <exception>
#include <iostream>

void InputLine::print() {
  InputLine::printTruthTable();
    std::cout << "Buttons: ";
    for (size_t i = 0; i < buttons.size(); ++i) {
      std::cout << "(";
      for (size_t j = 0; j < buttons[i].size()-1; ++j) {
        std::cout << buttons[i][j] << ",";
      }
      std::cout << buttons[i].back();
      std::cout << ") ";
    }
    std::cout << '\n';
    std::cout << "Joltage: {";
    for (size_t i = 0; i < joltage.size() - 1; ++i) {
      std::cout << joltage[i] << ",";
    }
    std::cout << joltage.back();
    std:: cout << "}\n";
}

void InputLine::printTruthTable() {
  std::cout << "Truthtable: ";
    for (size_t i = 0; i < truthTable.size(); ++i) {
      if (truthTable[i]) {
        std::cout << "#";
      } else {
        std::cout << ".";
      }
    }
    std::cout << '\n';

}

auto splitDelim(std::string& s, const std::string& delim) -> std::vector<std::string> {
  std::vector<std::string> tokens;
  size_t pos = 0;
  std::string token;
  while ((pos = s.find(delim)) != std::string::npos) {
    token = s.substr(0, pos);
    tokens.push_back(token);
    s.erase(0, pos+delim.length());
  }
  tokens.push_back(s);
  return tokens;
}

auto openFile(std::string fileName) -> std::vector<std::string> {
  std::ifstream myfile(fileName);
  std::string line;
  std::vector<std::string> input {};
  if (myfile.is_open()) {
    while (getline(myfile, line)) {
      input.push_back(line);
    }
  }
  return input;
}

auto extractTruthTable(std::string& line) -> std::vector<bool> {
  std::vector<bool> truthTable {};
  size_t start = line.find("[");
  size_t end = line.rfind("]");
  std::string_view substr = line.substr(start+1, end-start-1);
  for (size_t i = 0; i < substr.size(); ++i) {
    if (substr[i] == '.') {
      truthTable.push_back(false);
    } else if (substr[i] == '#') {
      truthTable.push_back(true);
    } else {
      throw std::invalid_argument("Non truth value item in extract truth table");
    }
  }
  return truthTable;
}

auto extractButtons(std::string& line) -> std::vector<std::vector<int>> {
  std::vector<std::vector<int>> buttons {};
  size_t start = line.find("(");
  size_t end = line.rfind(")");
  std::vector<std::string> temp {};
  for (size_t i = start; i < end; ++i) {
    if( line[i] == '(' ) {
      for (size_t j = i; j <= end; ++j) {
        if (line[j] == ')') {
          temp.push_back(line.substr(i+1, j - i - 1));
          break;
        }
      }
      continue;
    }
  }
  for (size_t i = 0; i < temp.size(); ++i) {
    auto effects {splitDelim(temp[i], ",")};
    std::vector<int> tempButtons {};
    for (size_t j = 0; j < effects.size(); ++j) {
      tempButtons.push_back(stoi(effects[j]));
    }
    buttons.push_back(tempButtons);
  }
  return buttons;
}

auto extractJoltage(std::string& line) -> std::vector<int> {
  std::vector<int> joltage {};
  size_t start = line.find("{");
  size_t end = line.rfind("}");
  std::string substr = line.substr(start+1, end-start-1);

  std::vector<std::string> jolt {splitDelim(substr, ",")};

  for(size_t i = 0; i < jolt.size(); ++i) {
    joltage.push_back(std::stoi(jolt[i]));
  }
  return joltage;
}

auto processLine (std::string& line) -> InputLine {
  std::vector<bool> truthTable = extractTruthTable(line);
  std::vector<std::vector<int>> buttons = extractButtons(line);
  std::vector<int> joltage = extractJoltage(line);
  InputLine output {truthTable, buttons, joltage};
  return output;
}

auto processFile(std::string fileName) -> std::vector<InputLine> {
  std::vector<std::string> raw = openFile(fileName);
  std::string truthTable {};
  std::vector<std::vector<int>> buttons {};
  std::vector<int> joltage {};
  std::vector<InputLine> output {};
  for (size_t i = 0; i < raw.size(); ++i) {
    InputLine input = processLine(raw[i]);
    output.push_back(input);
  }

  return output;
}

