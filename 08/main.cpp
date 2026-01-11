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
  }

  void print() {
    std::cout << "X: " << x << " Y: " << y << " Z: " << z << '\n';
  }

};

struct ConnectedNodes {
  Point firstNode;
  std::vector<Point> connections;

  auto addConnection(Point start, Point connection) {
    if (firstNode == start) {
      connections.push_back(connection);
    } else {
      firstNode = start;
      std::vector<Point> c {connection};
      connections = c;
    }
  }

  bool isConnected(Point connection) {
    if (connection == firstNode) {
      return true; // Should never end up here but if we do...
    }
    if (connections.size() > 0 ) {
      for (int i = 0; i < connections.size(); ++i) {
        if (connection == connections[i]) {
          return true;
        }
      }
    }
    return false;
  }

  void print() {
    firstNode.print();
    std:: cout << "Connections:\n";
    for (int i = 0; i < connections.size(); ++i) {
      connections[i].print();
    }
    std::cout << '\n';
  }

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

bool isConnected(std::vector<ConnectedNodes> c, Point p1, Point p2) {
  for (int i = 0; i < c.size(); ++i) {
    bool p1Found {false};
    bool p2Found {false};
    if (c[i].firstNode == p1) {
      p1Found = true;
    }
    if (c[i].firstNode == p2) {
      p2Found = true;
    }
    for (int j = 0; j < c[i].connections.size(); ++j) {
      Point temp {c[i].connections[j]};
      if (temp == p1) {
        p1Found = true;
      }
      if (temp == p2) {
        p2Found = true;
      }
    }
    if (p1Found && p2Found) {
      return true;
    }
  }
  return false;
}

std::vector<ConnectedNodes> findShortestDistances(std::vector<Point> points, std::vector<ConnectedNodes> connections) {
  float smallestDist {std::numeric_limits<float>::max()}; // Should be positive
  int loc0 {0}; // location in index where smallest point is
  int loc1 {0};
  for (int i = 0; i < points.size(); ++i) {
    for (int j = i; j < points.size(); ++j) {
      if (j != i) {
        float temp {distanceBetweenPoints(points[i], points[j])};
        if (temp < smallestDist && !isConnected(connections, points[i], points[j])) {
          smallestDist = temp;
          loc0 = i;
          loc1 = j;
        }
      }
    }
  }
  std::cout << "Smallest distance was found between points "
            << loc0 << " and " << loc1 << '\n';
  for (int i = 0; i < connections.size(); ++i) {
    if (connections[i].firstNode == points[loc0]) {
      connections[i].addConnection(points[loc0], points[loc1]);
      return connections;
    }
  }
  ConnectedNodes node {};
  node.addConnection(points[loc0], points[loc1]);
  connections.push_back(node);
  return connections;
}


auto main() -> int {
  std::vector<Point> points {processFile("example.txt")};
  printPoints(points);
  std::vector<ConnectedNodes> connections {};
  for (int i =0; i < 10; ++i) {
    std::cout << "Ran " << i << " times\n";
    connections =  findShortestDistances(points, connections);
  }
  for (int i = 0; i < connections.size(); ++i) {
    connections[i].print();
  }
  return 0;
}
