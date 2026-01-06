#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdexcept>
using namespace std;

// Directional offset to hopefully make calculating neighbors easier
struct DO{
  int x {};
  int y {};
};

// This is the format that returns when we remove boxes
// it consists of the new map after boxes are removed and the number
// of boxes we took away
struct RemovedBoxes{
  vector<vector<int>> map {};
  int numRemoved {};
};

auto openFile(string fileName) -> vector<vector<int>> {
  vector<vector<int>> output = {};
  ifstream myfile(fileName);
  string line;
  int lineNum {0};
  if (myfile.is_open()) {
    while (getline(myfile, line)){
      output.push_back(vector<int> {});
      int len = line.length();
      for (int c = 0; c < len; c++) {
        if (line[c] == '.') {
          output[lineNum].push_back(0);
          } else if (line[c] == '@') {
          output[lineNum].push_back(1);
        } else {
          throw invalid_argument("Received invalid line");
        }
      }
      lineNum++;
    }
  }
  return output;
}

bool isInVector(int xSize, int ySize, int x, int y) {
  if ((x >= 0 && x < xSize) && (y >= 0 && y < ySize)){
    return true;
  }
  return false;
}

int numNeighbors(vector<vector<int>> data, int x, int y) {
  vector<DO> offset {{0, 1}, {0, -1}, {1, 0}, {-1, 0},
      {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
  // Should be all of the directional offsets that we are concerned about
  int ySize = data.size();
  int xSize = data[0].size();
  int neighbor {};
  for (int d = 0; d < offset.size(); d++) {
    if (isInVector(xSize, ySize, x + offset[d].x, y + offset[d].y)) {
      neighbor += data[y + offset[d].y][x + offset[d].x];
    }
  }
  return neighbor;
}

void print2dArray(vector<vector<int>> data) {
  for (int i = 0; i < data.size(); i++) {
    for (int j = 0; j < data[i].size(); j++ ) {
      cout << data[i][j];
    } cout << '\n';
  }
}

RemovedBoxes removeBoxes (RemovedBoxes data) {
  cout << "Removed " << data.numRemoved << " boxes\n";
  vector<vector<int>> newData = data.map;
  int numRemoved = 0;
  for (int y = 0; y < data.map.size(); y++) {
    for (int x = 0; x < data.map[0].size(); x++) {
      if (numNeighbors(data.map, x, y) < 4 && data.map[y][x] == 1) {
        newData[y][x] = 0;
        numRemoved++;
      }
    }
  }
  int numIter = numRemoved + data.numRemoved;
  if (numRemoved != 0) {
    RemovedBoxes rm = removeBoxes({newData, numIter});
    newData = rm.map;
    numIter = rm.numRemoved;
  }
  return {newData, numIter};
}

auto main() -> int {
 // readFile() -> Vector<Vector<String>>
 // for i in j in File:
 // count adjacent cells
 // return 1 if moveable and 0 if not

  vector<vector<int>> input {};
  input = openFile("input04.txt");
  print2dArray(input);
  cout << "After removal\n";
  RemovedBoxes final = removeBoxes({input, 0});
  print2dArray(final.map);
  cout << final.numRemoved<< " total movable boxes \n";
  return 0;
}
