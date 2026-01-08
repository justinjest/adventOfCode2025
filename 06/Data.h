#ifndef DATA_H
#define DATA_H

#include <string>
#include <vector>


class Data {
  private:
  std::vector<int> numerals;
  std::string opp;

  long sumData();
  long multData();

  public:
  void printData();
  long processData();

  void setOpp(std::string s);
  void setNumeral(std::vector<int> n);

  std::string getOpp();
  std::vector<int> getNumeral();
};

#endif
