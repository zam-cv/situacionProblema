#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>

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
}

#endif