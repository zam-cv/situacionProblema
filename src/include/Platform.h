#ifndef PLATFORM_H
#define PLATFORM_H

#include <string>

class Platform {
private:
  bool isInvalid;

public:
  Platform();
  void run();
  void clear();
  void menu();
  void showTitle();
  char getOption();
  void loadFile();
};

#endif