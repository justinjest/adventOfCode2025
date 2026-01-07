#include <iostream>
#include <set>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

struct Range {
  long start;
  long end;
};



struct ProcessedData {
  vector<string> header; // This will get us the data to determine what is fresh
  vector<string> stock;  // This is what is in inventory
  vector<Range> ranges;

  void unpackHeader() {
    vector<Range> output {};
    for (int i = 0; i < header.size(); i++) {
       vector<string> strRange {split(header[i], "-")};
       long start = stol(strRange[0]);
       long end = stol(strRange[1]);
       Range out {start, end};
       output.push_back(out);
    }
    ranges = output;
  };


  // Splits a string at a delimiter
  auto split(std::string& s, const std::string& delim)
    -> std::vector<string>{
    std::vector<std::string> tokens;
    size_t pos = 0;
    std::string token;
    while ((pos = s.find(delim)) != std::string::npos) {
      token = s.substr(0, pos);
      tokens.push_back(token);
      s.erase(0, pos + delim.length());
    }
    tokens.push_back(s);
    return tokens;
  }

  bool isInRange(long num) {
    for (long i = 0; i < ranges.size(); i++) {
      if (num >= ranges[i].start && num <= ranges[i].end) {
        return true;
      }
    }
    return false;
  }
};

void printProcessedData(ProcessedData pd) {
  for (double i = 0; i < pd.ranges.size(); i++){
    cout << pd.ranges[i].start << " - " << pd.ranges[i].end << '\n';
  }
  for (double i = 0; i < pd.stock.size(); i++){
    cout << pd.stock[i] << '\n';
  }

};

auto preProcess (string fileName) -> ProcessedData {
  ifstream myfile(fileName);
  string line;
  ProcessedData output {};
  bool finishedHeader {false};
  if(myfile.is_open()) {
    while(getline(myfile, line)) {
      unsigned long len {line.length()};
      if (len == 0) {
        finishedHeader = true;
      }
      if (finishedHeader && len != 0) {
        output.stock.push_back(line);
       } else if (len != 0) {
        output.header.push_back(line);
      }
    }
  }
  output.unpackHeader();
  return output;
};

auto main() -> int {

  ProcessedData data {};
  data = preProcess("input05.txt");
  cout << "Pre processing finished\n";
  printProcessedData(data);
  long numFresh { 0 };
  for (long i = 0; i < data.stock.size(); i++){
    if(data.isInRange(stol(data.stock[i]))) {
      cout << data.stock[i] << " is fresh\n";
      numFresh++;
    }
  }
  cout << numFresh << " fresh ingredients found\n";
  return 0;
};
