#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <cctype>
#include <algorithm>

#include "Data.h"

using namespace std;


bool isWhitespace(std::string s){
    for(unsigned long index = 0; index < s.length(); index++){
        if(!std::isspace(s[index]))
            return false;
    }
    return true;
}

string justDigits(string& s) {
  string res {};
  for (int i = 0; i < s.length(); ++i) {
    if (isdigit(s[i])) {
      res.append(1, s[i]);
    }
  }
  return res;
}

vector<Data> processPart2 (vector<string> content) {
  vector<Data> res {};
  vector<int> values {};
  vector<vector<long>> allData {};
  string opp {};
  bool oppSet {false};
  for (unsigned long i = 0; i < content[1].size(); ++i) {
    if (!oppSet) {
      opp = content[content.size()-1][i];
      oppSet = true;
    }
    string value {""};
    for (unsigned long j = 0; j < content.size(); ++j){
      value.append(1, content[j][i]);
    }
    if (!isWhitespace(value) && !value.empty()){
      values.push_back(stoi(justDigits(value)));
    } else {
      oppSet = false;

      Data d {};
      d.setNumeral(values);
      d.setOpp(opp);

      values = {};

      res.push_back(d);
    }
  }
  // Have to run it one last time to get all items
  Data d {};
  d.setNumeral(values);
  d.setOpp(opp);

  values = {};

  res.push_back(d);

  return res;
}

vector<Data> openPart2(string fileName) {
  ifstream myfile(fileName);
  string line {};
  vector<string> content {};
  vector<vector<string>> temp {};
  if (myfile.is_open()) {
    while (getline(myfile, line)) {
      content.push_back(line);
    }
  }
  return processPart2(content);
}

auto openFile(string fileName) -> vector<Data> {
  vector<Data> output {};

  ifstream myfile(fileName);
  string line;
  vector<vector<string>> temp {};
  if (myfile.is_open()) {
    while (getline(myfile, line)) {
      stringstream ss(line);
      string word;
      vector<string> words;
      while (ss >> word) {
        cout << "word is |" << word << "|\n";
        words.push_back(word);
      }
      temp.push_back(words);
    }
  }
  for (unsigned long i = 0; i < temp[0].size(); ++i) {
    Data currLine {};
    vector<int> tmp {};
    currLine.Data::setOpp(temp[temp.size()][i]); // opp is always last in list
    for (unsigned long j = 0; j < temp.size(); ++j) {
     tmp.push_back(stoi(temp[j][i]));
    }
    currLine.Data::setNumeral(tmp);
    output.push_back(currLine);
  }
  return output;
}

auto part1() {
  vector<Data> data = openFile("example.txt");
  cout << "Data processed\n";
  long total {0};
  for (unsigned long i = 0; i < data.size();++i){
    data[i].printData();
    long value {data[i].Data::processData()};
    cout << "This useses the " << data[i].getOpp() <<
      " Opperator and the total is " << value << '\n';
    total += value;
  }
  cout << "The total of these operations is " << total << '\n';
}

auto main() -> int {
  vector<Data> data = openPart2("input06.txt");
  long sum {0};
  for (unsigned long i = 0; i < data.size(); ++i) {
    long processedNumber {data[i].processData()};
    data[i].printData();
    cout << "Result is " << processedNumber  << '\n';
    sum += processedNumber;
  }
  cout << "Total sum is " << sum << '\n';
  return 0;
}
