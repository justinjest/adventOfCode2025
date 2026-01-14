#ifndef UTIL_H_
#define UTIL_H_


#include <fstream>
#include <iostream>

auto openFile(std::string fileName) {
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




#endif // UTIL_H_
