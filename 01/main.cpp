#include <iostream>
#include <fstream>
#include <string>

using namespace std;

auto splitString(string textLine) -> int {
  if (textLine[0] == 'L') {
    // Left is subtraction

    std::string tmp = textLine.substr(1);
    int tmpInt = stoi(tmp);
    return -tmpInt;

  } else if (textLine[0] == 'R') {
    // Right is addition

    std::string tmp = textLine.substr(1);
    int tmpInt = stoi(tmp);
    return tmpInt;

  } else {
    std::cout << "Error spliting line found invalid paramater "
      << textLine;
    return 0;
  }
}

auto main() -> int {
  ifstream myfile("input01.txt");
  int countZero = 0;
  string line;
  if(myfile.is_open()) {
    int value = 50;
    while (getline (myfile, line)) {
      int split = splitString(line);
      if (split > 0) {
        //moving right
        for (int i = 0; i < split; i++){
          value ++;
          if (value == 100) {
            countZero ++;
            value = 0;
          }
        }
      } else if (split < 0) {
        //moving left
        for (int i = 0; i < split * -1; i++) {
          value = value - 1;
          if (value == 0) {
              countZero ++;
            }
          else if (value == -1) {
            value = 99;
          }
        }
      }
    }
    myfile.close();
  }
  else cout << "Unable to open file";
  cout << "Total number of zeros is " << countZero << '\n';
  return 0;
}
