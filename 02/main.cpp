#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

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

// Returns a vector of s split at length of frag
// Hello 3 -> ['hel', 'lo']
auto splitString(string s, int frag) -> vector<string>{
  vector<string> uni;
  int len = s.length();
  for (int i = 0; i < len; i+= frag) {
    uni.push_back(s.substr(i, frag));
  }
  return uni;
}

// Returns true if ID repeats itself otherwise false
// 11 = true
// 19 = false
auto isSillyId(string num) -> bool {
  int len = num.length();
  if (len % 2 != 0) {
    // Must be an even length to have 2 repeats
    return false;
  }
  if (num[0] == '0') {
    // if the number starts with a 0 it can not be valid
    cout << "Unexpected item in input " << num << '\n';
    return false;
  }
  vector<string> tmp = splitString(num, len/2);
  if (tmp[0] == tmp[1]) {
    cout << "Halves are " << tmp[0] << " & "<< tmp[1] << '\n';
    return true;
    }
  return false;
}

auto main() -> int {
  ifstream myfile("input02.txt");
  string line;
  long sum = 0;
  if(myfile.is_open()) {
    while (getline (myfile, line)) {
      std::vector<string> delim = split(line, ",");
      for (string i: delim) {
        std::vector<string> range = split(i, "-");
        long startRange = stol(range[0]);
        long endRange = stol(range[1]);
        for (long j = startRange; j <= endRange; j++) {
          if (isSillyId(to_string(j))) {
            // this feels bad
            cout << "invalid id " << j << '\n';
            sum += j;
            }
        }
      }
    }
    myfile.close();
  } else {
    cout << "Unable to open file";
  }
  cout << "Sum is " << sum << '\n';
  return 0;
}
