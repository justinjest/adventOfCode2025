#include <iostream>
#include <fstream>
#include <string>
#include <vector>

auto openFile(std::string fileName) -> std::vector<std::string>{

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

void printStringVector(std::vector<std::string> input) {
  for (int i = 0; i < input.size(); ++i) {
    std::cout << input[i] << '\n';
  }
}

std::string splitLineFirst (std::string& oldLine) {
  std::string newLine (oldLine.length(), '.');

  for (int i = 0; i < oldLine.length(); ++i) {
    char c = oldLine[i];
    switch (c) {
    case '.':
      if (newLine[i] != '|')
        newLine[i] = '.';
      break;
    case 'S':
      newLine[i] = '|';
      break;
      }
    }
  return newLine;
}

std::string splitLine (std::string& oldLine, std::string& currLine) {
  std::string newLine (currLine.length(), '.');
  static int splits {};
  for (int i = 0; i < currLine.length(); ++i) {
    char cCurr = currLine[i];
    char cLast = oldLine[i];
    switch (cCurr) {
    case '.':
      if (cCurr != '|' && cLast != '|')
        newLine[i] = '.';
      else if (cLast == '|' || newLine[i] == '|') {
        newLine[i] = '|';
      }
      break;
    case 'S':
      newLine[i] = '|';
      break;
    case '^':
      if (cLast == '|'){
        ++splits;
        newLine[i-1] = '|';
        newLine[i] = '^';
        newLine[i+1] = '|';
        currLine[i+1] = '|';
      } else {
        newLine[i] = '^';
      }
      break;
    case '|':
      newLine[i] = '|';
      break;
    }
  }
  std::cout << "Splits this line " << splits << '\n';
  return newLine;
}

std::vector<std::string> splitLinePart2(std::vector<std::string> input) {
  std::vector<std::string> output {};
  std::string newLine (input[0].length(), '.');
  static int splits {};
  for (int j = 1; j < input.size(); ++j) {
  for (int i = 0; i < input[0].length(); ++i) {
    char cCurr = input[j][i];
    char cLast = input[j][i - 1];
    switch (cCurr) {
    case '.':
      if (cCurr != '|' && cLast != '|')
        newLine[i] = '.';
      else if (cLast == '|' || newLine[i] == '|') {
        newLine[i] = '|';
      }
      break;
    case 'S':
      newLine[i] = '|';
      break;
    case '^':
      if (cLast == '|'){
        ++splits;
        newLine[i-1] = '|';
        newLine[i] = '^';
        newLine[i+1] = '|';
        input[j][i+1] = '|';
      } else {
        newLine[i] = '^';
      }
      break;
    case '|':
      newLine[i] = '|';
      break;
    }
  }
  output.push_back(newLine);
  }
  std::cout << "Splits this line " << splits << '\n';

  return output;
}

std::vector<std::string> processDataPart1 (std::vector<std::string> input) {
  std::vector<std::string> output { input };
  output = splitLinePart2(input);
  return output;
}


std::vector<std::string> processDataPart2 (std::vector<std::string> input) {
  std::vector<std::string> output {input};
  output = splitLinePart2(input);
  return output;
}

auto main() -> int {

  std::vector<std::string> rawData {openFile("input07.txt")};
  std::cout << "Output\n";
  std::vector<std::string> processedData {processDataPart1(rawData)};
  return 0;
}
