#include <iostream>
#include <fstream>
#include <vector>


struct Point {
  int x;
  int y;

  void print() {
    std::cout << "X: " << x << " Y: " << y << '\n';
  }

  long getArea(Point p1) {
    long side1 = (std::max(x, p1.x) - std::min(x, p1.x)) + 1;
    long side2 =  (std::max(y, p1.y) - std::min(y, p1.y)) + 1;
    return side1 * side2;
  }

};

bool inNet(std::vector<Point> points, Point p) {
  bool inNet {false};
  for (int i = 0; i < points.size(); ++i) {
    Point a = points[i];
    Point b= points[i-1];

    if (p.x == a.x && p.y == a.y)
      return true;

    if ((a.y > p.y) != (b.y > p.y)) {
      float slope = (p.x - a.x) * (b.y - a.y) - (b.x - a.x) * (p.y -a.y);
      if (slope == 0) // THis will probably error without rounding
        return true;
      if ((slope < 0) != (b.y < a.y))
        inNet = !inNet;
    }
  }
  return inNet;
}

std::vector<Point> rectPoints(Point p1, Point p2) {
  std::vector<Point> points {p1, p2};
  Point p3 {p1.x, p2.y};
  points.push_back(p3);
  Point p4 {p2.x, p1.y};
  points.push_back(p4);
  return points;
}

bool rectInNet(Point p1, Point p2, std::vector<Point> points) {
  std::vector<Point> rect {rectPoints(p1, p2)};
  for (int i =0; i < rect.size(); ++i) {
    if (!inNet(points, rect[i])) {
      return false;
    }
  }
  return true;
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


auto vecStrToVecInt(std::vector<std::string> input){
  std::vector<int> output {};
  for (int i = 0; i < input.size(); ++i) {
    output.push_back(stoi(input[i]));
  }
  return output;
}


auto strToPoint(std::string input) {
  Point p {};
  std::vector<std::string> rawVals {splitToInt(input, ",")};
  std::vector<int> intVals {vecStrToVecInt(rawVals)};
  if (rawVals.size() == 2) {
    p.x = intVals[0];
    p.y = intVals[1];
  }
  else {
    throw std::runtime_error("Too many values in strToPoint");
  }
  return p;
}

auto largestArea(std::vector<Point> points) {
  long largestArea {0};
  for (int i = 0; i < points.size(); ++i) {
    for (int j = i; j < points.size(); ++j) {
      long test = points[i].getArea(points[j]);
      if (largestArea < test && (rectInNet(points[i], points[j], points))) {
        largestArea = test;
      }
    }
  }

  std::cout << "Largest area is " << largestArea << '\n';
}


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


auto processFile(std::string fileName) {
  std::vector<std::string> raw = openFile(fileName);
  std::vector<Point> points {};
  for (int i = 0; i < raw.size(); ++i) {
    points.push_back(strToPoint(raw[i]));
  }
  return points;
}



auto main(int argc, char *argv[]) -> int {

  std::vector<Point> points {processFile("example.txt")};
  for (int i = 0; i < points.size(); ++i){
    points[i].print();
  }
  largestArea(points);
  return 0;
}
