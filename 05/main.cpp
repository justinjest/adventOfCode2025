#include <iostream>
#include <set>
#include <string>
#include <fstream>
#include <vector>

using namespace std;


struct ProcessedData {
  vector<string> header; // This will get us the data to determine what is fresh
  vector<string> stock;  // This is what is in inventory
};

struct FreshItems {
  set<long> freshItems;

  void addRange(string range) {
    long start {};
    long end {};
    vector<string> numbers = split(range, "-");
    start = stol(numbers[0]);
    end = stol(numbers[1]);

    for (long i = start; i <= end; i++ ) {
      cout << "adding item " << i << '\n';
      addFreshItem(i);
    }
  }

  void addFreshItem(long num) {
    freshItems.insert(num);
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

  auto isFresh(long num) -> bool {
    int count = freshItems.count(num);
    // Because this is a set this will either return 0 or 1 and maps to bool logic
    return count;
  }

};

void printProcessedData(ProcessedData pd) {
  for (double i = 0; i < pd.header.size(); i++){
    cout << pd.header[i] << '\n';
  }
  cout << "Starting stock list \n";
  for (double i = 0; i < pd.stock.size(); i++){
    cout << pd.stock[i] << '\n';
  }
}

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
  return output;
}

auto main() -> int {

  ProcessedData data {};
  data = preProcess("input05.txt");
  cout << "Pre processing finished\n";
  FreshItems freshList {};
  for (unsigned long i = 0; i < data.header.size(); i++) {
    cout << data.header[i] << '\n';
    freshList.addRange(data.header[i]);
  }

  cout << "Header processed\n";
  long totalFresh {0};
  for (unsigned long i = 0; i < data.stock.size(); i++) {
    if (freshList.isFresh(stoi(data.stock[i]))) {
      cout << data.stock[i] << " is fresh\n";
      totalFresh++;
    } else {
      cout << data.stock[i] << " is not fresh\n";
    }
  }

  cout << "In total " << totalFresh << " items are fresh\n";
  return 0;
}
