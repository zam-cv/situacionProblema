#ifndef DATE_H
#define DATE_H

#include <string>

class Date {
private:
  int day;
  int month;
  int year;

public:
  Date();
  Date(int, int, int);
  int getDay();
  int getMonth();
  int getYear();
  std::string toString();
};

#endif