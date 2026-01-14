#ifndef UTIL_H_
#define UTIL_H_


#include <fstream>
#include <string>
#include <vector>
#include <exception>
#include <iostream>

struct InputLine {
  std::vector<bool> truthTable;
  std::vector<std::vector<int>> buttons;
  std::vector<int> joltage;

  void print();
  void printTruthTable();

};

auto splitDelim(std::string& s, const std::string& delim) -> std::vector<std::string>;

auto openFile(std::string fileName) -> std::vector<std::string>;

auto extractTruthTable(std::string& line) -> std::vector<bool>;

auto extractButtons(std::string& line) -> std::vector<std::vector<int>>;

auto extractJoltage(std::string& line) -> std::vector<int>;

auto processLine (std::string& line) -> InputLine;

auto processFile(std::string fileName) -> std::vector<InputLine>;


#endif // UTIL_H_
