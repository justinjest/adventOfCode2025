#include <stdexcept>
#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>
#include <limits>
#include <algorithm>
#include <unordered_map>

struct Point {
  // 3d point in space
  int x;
  int y;
  int z;

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

class UnionFind {
  std::vector<int> parent;
  std::vector<int> numChildren;

public:
  UnionFind(int s) {
    parent.resize(s);
    numChildren.resize(s, 1);
    for (int i = 0; i < s; ++i){
      parent[i] = i;
    }
  }

  long getSize() {
    return parent.size();
  }

  int find(int i) {
    if (parent[i] == i) {
      return i;
    }
    return find(parent[i]);
  }

  void unite(int i, int j) {
    int irep = find(i);
    int jrep = find(j);
    if (irep == jrep){
      return;
      }
    parent[irep] = jrep;
    numChildren[jrep] += numChildren[irep];
  }

  int findNumChildren(int i) {
    int root = find(i);
    return numChildren[root];
  }

  void print(){
    for (int i = 0; i < parent.size(); ++i) {
      std::cout << parent[i] << ": ";
      std::cout << "Num children: " << findNumChildren(i) << '\n';
    }
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

UnionFind connectNode(UnionFind uf, int loc1, int loc2) {
  uf.unite(loc1, loc2);

  return uf;
}

UnionFind findShortestDistances(std::vector<Point> points, UnionFind uf) {
  float smallestDist {std::numeric_limits<float>::max()}; // Should be positive
  static float lastSmallest {0};
  int loc0 {0}; // location in index where smallest point is
  int loc1 {0};
  for (int i = 0; i < points.size(); ++i) {
    for (int j = i; j < points.size(); ++j) {
      float temp {distanceBetweenPoints(points[i], points[j])};
      if ((temp < smallestDist)
          && (temp > lastSmallest)) {
        smallestDist = temp;
        loc0 = i;
        loc1 = j;
      }
    }
  }
  lastSmallest = smallestDist;
  std::cout << "Last x * x " << points[loc0].x * points[loc1].x << '\n';
  return connectNode(uf, loc0, loc1);
}

auto ufToResult(UnionFind uf, int n) {
  std::unordered_map<int, int> componentSizes {};

  for (unsigned long i = 0; i < uf.getSize(); i++) {
    int root = uf.find(i);
    componentSizes[root] = uf.findNumChildren(root);
  }

  std::vector<int> sizes;
  for (const auto& kv : componentSizes) {
    sizes.push_back(kv.second);
  }
  std::sort(sizes.begin(), sizes.end(), std::greater<int>());

  long long res {1};
  for (unsigned long i = 0; i < n; ++i) {
    std::cout << sizes[i] << '\n';
    res *= sizes[i];
  }

  std::cout << "Final answer is " << res << '\n';
}

auto main() -> int {
  std::vector<Point> points {processFile("input08.txt")};
  printPoints(points);
  long size = points.size();
  UnionFind uf(size);
  int i {0};
  while (uf.findNumChildren(0) != points.size()) {
    std::cout << "Ran " << i << " times\n";
    ++i;
    uf = findShortestDistances(points, uf);
  }
  uf.print();
  return 0;
}
