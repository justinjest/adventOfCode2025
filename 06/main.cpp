#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

class Data {
  vector<int> numerals;
  string opp;

public:
  void printData() {
    for (int i = 0; i < numerals.size(); ++i) {
      cout << numerals[i] << " ";
    }
    cout << '\n';
    cout << "Operator is " << opp << '\n';
  }

  long processData() {
    if (opp == "+")
      return sumData();
    else if (opp == "*")
      return multData();
    else
      throw runtime_error("Invalid data command given");
  }

  void setOpp(string s){
    opp = s;
  }

  void setNumeral(vector<int> n) {
    numerals = n;
  }

  string getOpp () {
    return opp;
  }

  vector<int> getNumeral() {
    return numerals;
  }

private:
  long sumData() {
    long res {};
    for (int i = 0; i < numerals.size(); ++i) {
      res += numerals[i];
    }
    return res;
  }


  long multData() {
    long res {1}; // Initalize at 1 so we don't get mult by 0
    for (int i = 0; i < numerals.size(); ++i) {
      res = res * numerals[i];
    }
    return res;
  }
};

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
        words.push_back(word);
      }
      temp.push_back(words);
    }
  }
  cout << "Number of rows equals " << temp.size() << '\n';
  cout << "Number of cols equals " << temp[0].size() << '\n';
  for (int i = 0; i < temp[0].size(); ++i) {
    Data currLine {};
    vector<int> tmp {};
    currLine.setOpp(temp[temp.size() - 1][i]); // opp is always last in list
    cout << currLine.getOpp() << '\n';
    for (int j = 0; j < temp.size() - 1; ++j) {
     tmp.push_back(stoi(temp[j][i]));
    }
    currLine.setNumeral(tmp);
    output.push_back(currLine);
    currLine.printData();
  }
  return output;
}

auto main() -> int {

  vector<Data> data = openFile("example.txt");
  cout << "Data processed\n";
  long total {0};
  for (int i = 0; i < data.size();++i){
    data[i].printData();
    long value {data[i].processData()};
    cout << "This useses the " << data[i].getOpp() <<
      " Opperator and the total is " << value << '\n';
    total += value;
  }
  cout << "The total of these operations is " << total << '\n';
  return 0;
}
