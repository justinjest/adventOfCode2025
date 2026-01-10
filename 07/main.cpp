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

struct Position {
  char character;
  long number_splits;

  void init(char c, long i) {
    character = c;
    number_splits = i;
  }

  void addSplits(long n) {
    number_splits += n;
  }

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

std::vector<std::string> sliceVecStr (std::vector<std::string>& arr, int x, int y) {
  auto start = arr.begin() + x;
  auto end = arr.begin() + 1 + y;

  std::vector<std::string> res (y - x + 1);
  copy(start, end, res.begin());
  return res;
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
      newLine[i] = '|'; // Make this be an integer one, no need to print to screen
      break;
      }
    }
  return newLine;
}


SplitLine splitLine (std::string& oldLine, std::string& currLine) {
  std::string newLine (currLine.length(), '.');
  int splits {};
  int paths {};
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
      if (oldLine[i-1]) {
        ++paths;
      }
      if (oldLine[i+1]) {
        ++paths;
      }
      newLine[i] = '|';
      break;
    }
  }
  SplitLine output {newLine, paths};
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

void printArrayData(std::vector<std::vector<Position>> input) {
  for (int i = 0; i < input.size(); ++i) {
    for (int j = 0; j < input[0].size(); ++j) {
      std::cout << input[i][j].character;
    }
    std::cout << '\n';
  }
}

std::vector<std::vector<Position>> processInput(std::vector<std::string> input) {
  std::vector<std::vector<Position>> result {};
  for (int i = 0; i < input.size(); ++i) {
    std::vector<Position> temp {};
    for (int j = 0; j < input[0].size(); j++) {
      Position p {};
      if (input[i][j] == 'S') {
        p.init('|', 1);
      }
      else {
        p.init(input[i][j], 0);
      }
      temp.push_back(p);
    }
    result.push_back(temp);
  }
  return result;
}

void processData3(std::vector<std::string> input) {
  // In this we one we are going to read the open file and extract it
  // into a vec(vec(bit)) which I can use to propogate the number of
  // splits this takes
  std::vector<std::vector<Position>> result = processInput(input);

  for (int i = 1; i < result.size(); ++i) {
    for (int j = 0; j < result[0].size(); ++j) {
    // TESTING

    Position curr = result[i][j];
    char cCurr = curr.character;
    Position last = result[i-1][j];
    char cLast = last.character;

    switch (cCurr) {
    case '.':
      if (cCurr != '|' && cLast != '|')
        result[i][j].character = '.';
      else if (cLast == '|' || cCurr == '|') {
        result[i][j].character = '|';
      }
      break;
    case '^':
      if (cLast == '|'){
        result[i][j-1].character = '|';
        result[i][j+1].character = '|';
      }
      break;
    case '|':
      break;
    }
    // TESTING
    }
  }
  std::cout << "End of testing\n";
  printArrayData(result);
}


auto main() -> int {

  std::vector<std::string> rawData {openFile("example.txt")};
  //std::cout << "Output\n";
  //std::vector<std::string> datapart1 = processData1(rawData);
  //printStringVector(datapart1);
  //std::cout << "Refactored\n";
  processData3(rawData);
  return 0;
}
