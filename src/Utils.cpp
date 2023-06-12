#include "./include/Utils.h"
#include <string>

namespace Font {
  std::string bold(std::string text) {
    return "\033[1m" + text + "\033[0m";
  }

  std::string underline(std::string text) {
    return "\033[4m" + text + "\033[0m";
  }

  std::string italic(std::string text) {
    return "\033[3m" + text + "\033[0m";
  }
}

namespace Color {
  std::string red(std::string text) {
    return "\033[31m" + text + "\033[0m";
  }

  std::string blue(std::string text) {
    return "\033[34m" + text + "\033[0m";
  }

  std::string yellow(std::string text) {
    return "\033[33m" + text + "\033[0m";
  }

  std::string green(std::string text) {
    return "\033[32m" + text + "\033[0m";
  }

  std::string cyan(std::string text) {
    return "\033[36m" + text + "\033[0m";
  }

  std::string magenta(std::string text) {
    return "\033[35m" + text + "\033[0m";
  }

  std::string gray(std::string text) {
    return "\033[1;30m" + text + "\033[0m";
  }
}

namespace String {
  std::string trim(std::string text) {
    int start = 0;
    int end = text.size() - 1;

    while (text[start] == ' ') {
      start++;
    }

    while (text[end] == ' ') {
      end--;
    }

    return text.substr(start, end - start + 1);
  }

  std::vector<std::string> split(std::string text, char delimiter) {
    std::vector<std::string> result;
    std::string word = "";

    for (int i = 0; i < text.size(); i++) {
      if (text[i] == delimiter) {
        result.push_back(word);
        word = "";
      } else {
        word += text[i];
      }
    }

    if (word != "") {
      result.push_back(word);
    }

    return result;
  }

  std::string join(std::vector<std::string> text, char delimiter) {
    std::string result = "";

    for (int i = 0; i < text.size(); i++) {
      result += text[i];

      if (i != text.size() - 1) {
        result += delimiter;
      }
    }

    return result;
  }
}