#include "./include/Utils.h"
#include <string>
#include <cctype>
#include <iomanip>
#include <sstream>
#include <iostream>

namespace Font {
  // Convierte el texto a negrita
  std::string bold(std::string text) {
    return "\033[1m" + text + "\033[0m";
  }

  // Subraya el texto
  std::string underline(std::string text) {
    return "\033[4m" + text + "\033[0m";
  }

  // Convierte el texto a cursiva
  std::string italic(std::string text) {
    return "\033[3m" + text + "\033[0m";
  }
}

// Da color al texto
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
  // Elimina los espacios en blanco al inicio y al final del texto
  std::string trim(std::string text) {
    int start = 0;
    int end = text.size() - 1;

    // Mientras el caracter en la posición start sea un espacio en blanco
    while (text[start] == ' ') start++;

    // Mientras el caracter en la posición end sea un espacio en blanco
    while (text[end] == ' ') end--;

    // Retorna el texto desde la posición start hasta la posición end
    return text.substr(start, end - start + 1);
  }

  // Divide el texto en un vector de strings
  std::vector<std::string> split(std::string text, char delimiter) {
    std::vector<std::string> result;
    std::string word = "";

    // Recorre el texto caracter por caracter
    for (int i = 0; i < text.size(); i++) {
      // Si el caracter es igual al delimitador
      if (text[i] == delimiter) {
        result.push_back(word);
        word = "";
      } else { // Si no se concatena el caracter al string word
        word += text[i];
      }
    }

    // Si el string word no está vacío se agrega al vector result
    if (word != "") result.push_back(word);

    return result;
  }

  // Une los elementos de un vector de strings en un solo string
  std::string join(std::vector<std::string> text, char delimiter) {
    std::string result = "";

    // Recorre el vector de strings
    for (int i = 0; i < text.size(); i++) {
      result += text[i];

      // Si no es el último elemento se agrega el delimitador
      if (i != text.size() - 1) result += delimiter;
    }

    return result;
  }

  // Une los elementos de un set de strings en un solo string
  std::string join(std::set<std::string> text, char delimiter) {
    std::string result = "";
    int i = 0;

    // Recorre el set de strings
    for (auto it = text.begin(); it != text.end(); it++) {
      // Agrega el elemento al string result
      result += *it;

      // Si no es el último elemento se agrega el delimitador
      if (i != text.size() - 1) {
        result += delimiter;
      }

      i++;
    }

    return result;
  }

  // Convierte el texto a minúsculas
  std::string toLower(std::string text) {
    std::string result = "";

    // Recorre el texto caracter por caracter
    for (int i = 0; i < text.size(); i++) {
      // Convierte el caracter a minúscula y lo agrega al string result
      result += std::tolower(text[i]);
    }

    return result;
  }

  // Convierte el texto a entero
  int toInt(std::string text) {
    // Intenta convertir el texto a entero
    // Si no se puede retorna 0
    try {
      return std::stoi(text);
    } catch (std::invalid_argument const &e) {
      return -1;
    } catch (std::out_of_range const &e) {
      return -1;
    }
  }

  // Convierte el texto a double
  double toDouble(std::string text) {
    // Intenta convertir el texto a double
    // Si no se puede retorna 0
    try {
      return std::stod(text);
    } catch (std::invalid_argument const &e) {
      return -1;
    } catch (std::out_of_range const &e) { 
      return -1;
    } 
  }

  // Reemplaza todas las ocurrencias de un string por otro
  std::string replace(std::string text, std::string from, std::string to) {
    std::string result = "";
    std::string word = "";

    // Recorre el texto caracter por caracter
    for (int i = 0; i < text.size(); i++) {
      // Si el caracter es igual al primer caracter de la palabra a reemplazar
      if (text[i] == from[0]) {
        bool match = true;

        // Verifica si la palabra a reemplazar está en el texto
        for (int j = 0; j < from.size(); j++) {
          if (text[i + j] != from[j]) {
            match = false;
            break;
          }
        }

        // Si la palabra está en el texto se reemplaza
        if (match) {
          result += to;
          i += from.size() - 1;
        } else {
          result += text[i];
        }
      } else { // Si no se concatena el caracter al string result
        result += text[i];
      }
    }

    return result;
  }
}

namespace Number {
  // Un double se convierte a string con una precisión determinada
  std::string withPrecision(double number, int precision) {
    std::stringstream stream;
    stream << std::fixed << std::setprecision(precision) << number;
    return stream.str();
  }
  
  // Verifica si un número está en un rango determinado
  bool inRange(int number, int min, int max) {
    return number >= min && number <= max;
  }

  // Verifica si un numero está entre un rango determinado
  bool isBetween(int number, int min, int max) {
    return number > min && number < max;
  }

  // Convierte un número a string
  std::string toStr(int number) {
    std::stringstream stream;
    stream << number;
    return stream.str();
  }
}

namespace Console {
  // Pide una entrada al usuario
  std::string input(std::string text) {
    std::cout << text;
    std::string result;
    std::getline(std::cin, result);
    return result;
  }

  // Pausa la ejecución del programa
  void pause() {
    std::cin.ignore();
  }

  // Pausa la ejecución del programa y muestra un texto
  void pause(std::string text) {
    std::cout << text;
    std::cin.ignore();
  }
}