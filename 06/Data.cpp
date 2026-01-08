#include "Data.h"

#include <iostream>
#include <stdexcept>

  void Data::printData() {
    for (unsigned long i = 0; i < numerals.size(); ++i) {
      std::cout << numerals[i] << " ";
    }
    std::cout << '\n';
    std::cout << "Operator is " << opp << '\n';
  }

  long Data::processData() {
    if (opp == "+")
      return sumData();
    else if (opp == "*")
      return multData();
    else
      throw std::runtime_error("Invalid data command given");
  }

  void Data::setOpp(std::string s){
    opp = s;
  }

  void Data::setNumeral(std::vector<int> n) {
    numerals = n;
  }

  std::string Data::getOpp () {
    return opp;
  }

  std::vector<int> Data::getNumeral() {
    return numerals;
  }

  long Data::sumData() {
    long res {};
    for (unsigned long i = 0; i < numerals.size(); ++i) {
      res += numerals[i];
    }
    return res;
  }


  long Data::multData() {
    long res {1}; // Initalize at 1 so we don't get mult by 0
    for (unsigned long i = 0; i < numerals.size(); ++i) {
      res = res * numerals[i];
    }
    return res;
  }
