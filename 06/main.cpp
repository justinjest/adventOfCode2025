#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <cctype>

#include "Data.h"

using namespace std;




bool isWhitespace(std::string s){
    for(unsigned long index = 0; index < s.length(); index++){
        if(!std::isspace(s[index]))
            return false;
    }
    return true;
}

vector<Data> openPart2(string fileName) {
  vector<Data> output {};

  ifstream myfile(fileName);
  string line;
  vector<string> content {};
  vector<vector<string>> temp {};
  if (myfile.is_open()) {
    while (getline(myfile, line)) {
      content.push_back(line);
    }
  }
  vector<string> values {};
  vector<vector<long>> allData {};
  for (unsigned long i = 0; i <= content[0].size(); ++i) {
    string value {""};
    for (unsigned long j = 0; j < content.size()-1; ++j){
      value.append(1, content[j][i]);
    }
    if (!isWhitespace(value) && !value.empty()){
      values.push_back(value);
      }
  }
  cout << "Items in list\n";
  vector<int> test {};
  for (unsigned long item = 0; item < values.size(); ++item) {
    string s = values[item];
    cout <<"|"<< values[item] <<"|"<< "itemSize " <<
      values[item].size() <<'\n';
    int i {stoi(values[item])};
    test.push_back(i);
  }
  return output;
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
    currLine.Data::setOpp(temp[temp.size() - 1][i]); // opp is always last in list
    for (unsigned long j = 0; j < temp.size() - 1; ++j) {
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
  openPart2("example.txt");
  return 0;
}
