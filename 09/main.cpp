#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <algorithm>
#include <unordered_map>

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

bool inNetUp(std::vector<Point>& points, Point& p) {
  bool inNet {false};
  for (int i = 0; i < points.size(); ++i) {
    Point a = points[i];
    Point b {};
    if (i == 0) {
      b = points.back();
    } else {
      b = points[i-1];
    }

    if (p.x == a.x && p.y == a.y)
      return true;

    if ((a.x > p.x) != (b.x > p.x)) {
      long slope = (p.y - a.y) * (b.x - a.x) - (b.y - a.y) * (p.x - a.x);
      if (slope == 0)
        return true;
      if ((slope < 0) != (b.x < a.x))
        inNet = !inNet; // This tracks the even/oddness of it
    }
  }
  return inNet;
}


bool inNetRight(std::vector<Point>& points, Point& p) {
  bool inNet {false};
  for (int i = 0; i < points.size(); ++i) {
    Point a = points[i];
    Point b {};
    if (i == 0) {
      b = points.back();
    } else {
      b = points[i-1];
    }

    if (p.x == a.x && p.y == a.y)
      return true;

    if ((a.y > p.y) != (b.y > p.y)) {
      long slope = (p.x - a.x) * (b.y - a.y) - (b.x - a.x) * (p.y -a.y);
      if (slope == 0) // THis will probably error without rounding
        return true;
      if ((slope < 0) != (b.y < a.y))
        inNet = !inNet; // This tracks the even/oddness of it
    }
  }
  return inNet;
}

bool inNet(std::vector<Point>& points, Point& p) {
  return (inNetRight(points, p) || inNetUp(points, p));
}

void printRect(std::vector<Point> net) {
  std::cout << "New net\n";
  for (int i = 0; i < net.size(); ++i) {
    net[i].print();
  }
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
  int minX {std::min(p1.x, p2.x)};
  int minY {std::min(p1.y, p2.y)};
  int maxX {std::max(p1.x, p2.x)};
  int maxY {std::max(p1.y, p2.y)};
  for (int x = minX; x <= maxX; ++x) {
      rect.push_back( Point {x, minY});
      rect.push_back(Point {x, maxY});
  }
  for (int y = minY; y <= maxY; ++y) {
    rect.push_back(Point{minX, y});
    rect.push_back(Point{maxX, y});
  }
  for (int i = 0; i < rect.size(); ++i) {
    if (!inNet(points, rect[i])) {
      return false;
    }
  }
  return true;
}

long determinant(Point p, Point q, Point r) {
  return(((q.x - p.x) * (r.y - p.y)) - ((q.y - p.y) * (r.x - p.x)));
}

bool isIntersection(Point a, Point b, Point c, Point d) {
  long d1 = determinant(a, b, c);
  long d2 = determinant(a, b, d);
  long d3 = determinant(c, d, a);
  long d4 = determinant(c, d, b);

  return ((d1 * d2) < 0 && (d3 * d4) < 0);
}

bool netIntersection(Point p1, Point p2, std::vector<Point> points) {
  int minX {std::min(p1.x, p2.x)};
  int minY {std::min(p1.y, p2.y)};
  int maxX {std::max(p1.x, p2.x)};
  int maxY {std::max(p1.y, p2.y)};

  Point r1 {minX, minY};
  Point r2 {minX, maxY};
  Point r3 {maxX, minY};
  Point r4 {maxX, maxY};

  for (int i = 0; i < points.size(); ++i) {
    Point e1 {points[i]};
    Point e2 {i != 0 ? points[i-1] : points.back()};

    bool b1 {isIntersection(r1, r2, e1, e2)};
    bool b2 {isIntersection(r4, r2, e1, e2)};
    bool b3 {isIntersection(r3, r4, e1, e2)};
    bool b4 {isIntersection(r1, r3, e1, e2)};

    if ((b1 || b2 || b3 || b4)) {
      return true;
    }
  }
  return false;
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
  long size = points.size();
  long largestArea {0};
  for (int i = 0; i < size; ++i) {
    for (int j = i; j < size; ++j) {
      std::cout << "Outer loops done " << i;
      std::cout << " Inner loops done " << j << '\n';
      long test = points[i].getArea(points[j]);
      if (largestArea < test && (rectInNet(points[i], points[j], points))) {
        std::cout << "New largest area " << test << '\n';
        largestArea = test;
      }
    }
  }
  std::cout << "Largest area is " << largestArea << '\n';
}


auto largestArea2(std::vector<Point> points) {
  long size = points.size();
  long largestArea {0};
  for (int i = 0; i < size; ++i) {
    for (int j = i; j < size; ++j) {
      //std::cout << "Outer loops done " << i;
      //std::cout << " Inner loops done " << j << '\n';
      long test = points[i].getArea(points[j]);
      if (largestArea < test && !netIntersection(points[i], points[j], points)) {
        //std::cout << "New largest area " << test << '\n';
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
  largestArea(points); // Should be 24

  std::vector<Point> ex01 {processFile("testCase01.txt")};
  largestArea(ex01); // Should be 30
  std::vector<Point> ex02 {processFile("testCase02.txt")};
  largestArea(ex02); // Should be 88


// This tests for islands in the data; we do not have any
//  std::vector<Point> ex03 {processFile("testCase03.txt")};
//  largestArea(ex03); // Should be 72

  points = processFile("input09.txt");
  largestArea(points);

  return 0;
}
