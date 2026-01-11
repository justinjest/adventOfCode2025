#include <stdexcept>
#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>
#include <limits>

struct Point {
  // 3d point in space
  int x;
  int y;
  int z;
  bool connected;

  void printPoint(){
    std::cout << "X: " << x << '\n';
    std::cout << "Y: " << y << '\n';
    std::cout << "Z: " << z << '\n';
  }
  bool operator==(const Point& rhs) const
  {
     return (x== rhs.x)
     && (y == rhs.y)
     && (z == rhs.z);
  };
};


auto openFile(std::string fileName) {
  std::ifstream myfile(fileName);
  std::string line;
  std::vector<std::string> input {};

  if (myfile.is_open()) {
    while (getline(myfile, line)) {
      input.push_back(line);
    }
  }
  return input;
}

auto vecStrToVecInt(std::vector<std::string> input){
  std::vector<int> output {};
  for (int i = 0; i < input.size(); ++i) {
    output.push_back(stoi(input[i]));
  }
  return output;
}

auto splitToInt(std::string& s, const std::string& delim) {
  std::vector<std::string> tokens;
  size_t pos = 0;
  std::string token;
  while ((pos = s.find(delim)) != std::string::npos) {
    token = s.substr(0, pos);
    tokens.push_back(token);
    s.erase(0, pos+delim.length());
  }
  tokens.push_back(s);
  return tokens;
}

auto strToPoint(std::string input) {
  Point p {};
  std::vector<std::string> rawVals {splitToInt(input, ",")};
  std::vector<int> intVals {vecStrToVecInt(rawVals)};
  if (rawVals.size() == 3) {
    p.x = intVals[0];
    p.y = intVals[1];
    p.z = intVals[2];
    p.connected = false;
  }
  else {
    throw std::runtime_error("Too many values in strToPoint");
  }

  return p;
}

auto processFile(std::string fileName) {
  std::vector<std::string> raw = openFile(fileName);

  std::vector<Point> points {};
  for (int i = 0; i < raw.size(); ++i) {
    points.push_back(strToPoint(raw[i]));
  }
  return points;
}

float distanceBetweenPoints(Point p1, Point p2) {
  float dist = std::sqrt  ((pow(p1.x - p2.x, 2))
                         + (pow(p1.y - p2.y, 2))
                         + (pow(p1.z - p2.z, 2)));
  return dist;
}

void printPoints(std::vector<Point> in) {
  std::cout << "Now printing\n";
  for (int i = 0; i < in.size(); ++i) {
    std::cout << "Loc: " << i << " X: " << in[i].x <<
      " Y: " << in[i].y <<
      " Z: " << in[i].z << '\n';
  }
}

std::vector<Point> findShortestDistances(std::vector<Point> points) {
  float smallestDist {std::numeric_limits<float>::max()}; // Should be positive
  int loc0 {0}; // location in index where smallest point is
  int loc1 {0};
  for (int i = 0; i < points.size(); ++i) {
    for (int j = i; j < points.size(); ++j) {
      if (j != i) {
        float temp {distanceBetweenPoints(points[i], points[j])};
        if (temp < smallestDist) {
          smallestDist = temp;
          loc0 = i;
          loc1 = j;
          // This finds a single smallest point; running it
          // for the 1,000 closest points will take 1000 more runs
        }
      }
    }
  }
  std::cout << "Smallest distance was found between points "
            << loc0 << " and " << loc1 << '\n';
  std::vector<Point> result {points[loc0], points[loc1]};
  return result;
}


void printConnections(std::vector<std::vector<Point>> connections) {
  for (int i = 0; i < connections.size(); ++i) {
    printPoints(connections[i]);
  }
}

void connectTwoPoints(Point p1, Point p2, std::vector<std::vector<Point>> connections) {
  if (!p1.connected && !p2.connected) {
    std::vector<Point> temp {p1, p2};
    connections.push_back(temp);
  } else if (p1.connected && p2.connected) {
    return;
  } else {
    for (int i = 0;  i < connections.size(); ++i) {
      for (int j = 0; j < connections[0].size(); ++j) {
        Point pTemp { connections[i][j] };
        if(p1 == pTemp) {
          connections[i].push_back(p1);
        }
        else if (p2 == pTemp) {
          connections[i].push_back(p2);
        }
      }
    }
  }
  printConnections(connections);
}

auto main() -> int {
  std::vector<Point> points {processFile("example.txt")};
  printPoints(points);
  std::vector<Point> pair {findShortestDistances(points)};
  std::vector<std::vector<Point>> empty {};
  std::cout << empty.size() << '\n';
  for (int i = 0; i < 10; ++i){
    connectTwoPoints(Pair[0], Pair[1], empty);

  }
  return 0;
}
