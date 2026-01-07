#include <algorithm>
#include <iostream>
#include <set>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

struct ProcessedData {
  vector<string> header; // This will get us the data to determine what is fresh
  vector<string> stock;  // This is what is in inventory
  vector<vector<long>> ranges;

  void unpackHeader() {
    vector<vector<long>> output {};
    for (int i = 0; i < header.size(); i++) {
       vector<string> strRange {split(header[i], "-")};
       long start = stol(strRange[0]);
       long end = stol(strRange[1]);
       vector<long> out {start, end};
       output.push_back(out);
    }

    ranges = mergeRanges(output);
  };

  // This function comes from https://www.geeksforgeeks.org/dsa/merging-intervals/
  // I do not understand it as well as I should
  vector<vector<long>> mergeRanges(vector<vector<long>> &arr) {
    int n = arr.size();

    sort(arr.begin(), arr.end());
    vector<vector<long>> res;

    for (int i = 0; i < n; i++) {
      long start = arr[i][0];
      long end = arr[i][1];

      if (!res.empty() && res.back()[1] >= end) {
        continue;
      }
      for (int j = i + 1; j < n; j++) {
        if (arr[j][0] <= end)
          end = max(end, arr[j][1]);
      }
      res.push_back({start, end});
    }
    return res;
  }

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
      if (num >= ranges[i][0] && num <= ranges[i][1]) {
        return true;
      }
    }
    return false;
  }

};

void printProcessedData(ProcessedData pd) {
  for (double i = 0; i < pd.ranges.size(); i++){
    cout << pd.ranges[i][0] << " - " << pd.ranges[i][1] << '\n';
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

int countFresh(ProcessedData data) {
  long numFresh { 0 };
  for (long i = 0; i < data.stock.size(); i++){
    if(data.isInRange(stol(data.stock[i]))) {
      cout << data.stock[i] << " is fresh\n";
      numFresh++;
    }
  }
  cout << numFresh << " fresh ingredients found\n";
  return numFresh;
};

int countFreshIngredients(ProcessedData data) {
  long totalFresh {0};
  for (long i = 0; i < data.ranges.size(); i++) {
    cout << data.ranges[i][0] << " - " << data.ranges[i][1] << "\n";
    totalFresh += data.ranges[i][1] - data.ranges[i][0] + 1;
  }
  cout << totalFresh << " potentially fresh ingredients\n";
  return totalFresh;
}

auto main() -> int {

  ProcessedData data {};
  data = preProcess("input05.txt");
  cout << "Pre processing finished\n";
  printProcessedData(data);
  countFresh(data);
  countFreshIngredients(data);
  return 0;
};
