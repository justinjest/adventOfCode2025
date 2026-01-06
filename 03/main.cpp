#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

using namespace std;


struct BatteryJoltage {
  int value {};
  long loc {};
};


auto getNextNumber(string line, BatteryJoltage lastVal) -> BatteryJoltage {
  int largestNumber {};
  long loc{};
  int len = line.length();
  for (int i = lastVal.loc+1; i < len; i++){
    int num = int(line[i]) - 48; // 48 is ascii for 0 this is clamped 1-9
    if (num > largestNumber) {
      largestNumber = num;
      loc = i;
    }
  }
  cout << "Found second largest num " << largestNumber << " at "
       << loc << '\n';
  return {largestNumber, loc};
}

auto getJoltage (string line) -> int {
  int largestNumber {}; // should be between 1-9 in output
  long loc {};
  int len = line.length();
  for (int i = 0; i < len-1; i++) {
    // This method of converting char to int can't be right
    int num = int(line[i]) - 48; // 49 is ascii for 0 this is clamped 1-9
    if (num > largestNumber) {
      largestNumber = num;
      loc = i;
    }
  }
  cout << "Found largest num " << largestNumber << " at " << loc << '\n';
  BatteryJoltage second {getNextNumber(line, {largestNumber, loc})};
  return (largestNumber * 10) + second.value;
}

auto getNextOverload (string line, BatteryJoltage lastJoltage, int cap)
  -> BatteryJoltage {
  // cap prevents us from going too far into the string
  int largestNumber {};
  long loc{};
  int nextLocation {0};
  // If a zero initializion has been done we want to start search at 0
  // otherwise we want to add 1 to previous loc
  // Because value can never be 0 unless we did a zero initilaziation this
  // should catch that for us.
  if (lastJoltage.value > 0) {
    nextLocation = 1;
  }
  for (int i = lastJoltage.loc + nextLocation; i <= cap; i++){
    int num = int(line[i]) - 48; // 48 is ascii for 0 this is clamped 1-9
    if (num > largestNumber) {
      largestNumber = num;
      loc = i;
    }
  }
  return {largestNumber, loc};
}

auto getOverloadJoltage (string line) -> long long{
  double multiplier {pow(10, 11)};
  long long output {0};
  BatteryJoltage lastJoltage = {0, 0}; // initalize a zero value for this

  for (int i = 0; i < 12; i++) {
    lastJoltage = getNextOverload(line, lastJoltage, line.length() - (12 - i));
    output = output + (lastJoltage.value * multiplier);
    multiplier = multiplier / 10;
  }
  return output;
}

auto main() -> int {
  ifstream myfile("input03.txt");
  string line;
  unsigned long long sum {};
  if (myfile.is_open()) {
    while (getline (myfile, line)) {
      double joltage = getOverloadJoltage(line);
      sum += joltage;
    }
  }
  cout << "Total joltage possible is " << sum << '\n';
  return 0;
}
