#include "./include/Platform.h"

#include <iostream>
#include <string>

static const std::string title = "Plataforma de Streaming";

Platform::Platform() {}

void Platform::run() {
  while (true) {
    this->clear();
    this->showTitle();
    this->menu();
  }
}

void Platform::menu() {
  std::cout << "1. Cargar archivo de datos" << std::endl
            << "3. Buscar video" << std::endl
            << "4. Buscar serie" << std::endl
            << "5. Buscar pelicula" << std::endl
            << "6. Calificar video\n\n";

  char option;
  std::cout << "❯ ";
  std::cin >> option;
}

void Platform::showTitle() {
  std::cout << "\033[34m======\033[0m " << title
            << " \033[34m======\033[0m\n\n";
}

void Platform::clear() { std::system("clear"); }