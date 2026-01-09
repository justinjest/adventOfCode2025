#include <iostream>
#include <fstream>
#include <string>
#include <vector>


struct Result {
  std::vector<std::string> result;
  int splits;
};

struct SplitLine {
  std::string newLine;
  int splits;
};

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

SplitLine splitLine (std::string& oldLine, std::string& currLine) {
  std::string newLine (currLine.length(), '.');
  int splits {};
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
  SplitLine output {newLine, splits};
  return output;
}

Result processData2(std::vector<std::string> input) {
  std::vector<std::string> output {input};
  static int splits {};
  output[0] = splitLineFirst(output[0]);
  long unsigned len { output.size() };
  for (int j = 1; j < len; ++j) {
    SplitLine temp {splitLine(output[j-1], output[j])};
    output[j] = temp.newLine;
    splits += temp.splits;
    }
  Result res {output, splits};
  return res;
}

std::vector<std::string> processData1 (std::vector<std::string> input) {
  std::vector<std::string> output { input };
  output[0] = splitLineFirst(output[0]);
  for (int i = 1; i < output.size(); ++i) {
    output[i] = splitLine(output[i-1], output[i]).newLine;
  }
  return output;
}


auto main() -> int {

  std::vector<std::string> rawData {openFile("example.txt")};
  std::cout << "Output\n";
  //std::vector<std::string> datapart1 = processData1(rawData);
  //printStringVector(datapart1);
  Result datapart2 {processData2(rawData)};
  printStringVector(datapart2.result);
  std::cout << "Splits this line " << datapart2.splits << '\n';
  return 0;
}
