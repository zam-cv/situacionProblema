#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>
#include <set>

namespace Font {
  std::string bold(std::string text);
  std::string italic(std::string text);
  std::string underline(std::string text);
}

namespace Color {
  std::string red(std::string text);
  std::string blue(std::string text);
  std::string yellow(std::string text);
  std::string green(std::string text);
  std::string cyan(std::string text);
  std::string magenta(std::string text);
  std::string gray(std::string text);
}

namespace String {
  std::string trim(std::string text);
  std::vector<std::string> split(std::string text, char delimiter);
  std::string join(std::vector<std::string> text, char delimiter);
  std::string join(std::set<std::string> text, char delimiter);
  std::string toLower(std::string text);
  int toInt(std::string text);
  double toDouble(std::string text);
  std::string replace(std::string text, std::string from, std::string to);
}

namespace Number {
  std::string withPrecision(double number, int precision);
  std::string toStr(int number);
  bool inRange(int number, int min, int max);
  bool isBetween(int number, int min, int max);
}

namespace Console {
  std::string input(std::string text);
  void pause(std::string text);
  void pause();
}

#endif