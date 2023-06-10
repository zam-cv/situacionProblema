#include "./include/Platform.h"

#include <iostream>
#include <string>

static const std::string title = "Plataforma de Streaming";

Platform::Platform() { this->isInvalid = false; }

void Platform::run() {
  while (true) {
    this->clear();
    this->showTitle();
    this->menu();
  }
}

char Platform::getOption() {
  char option;

  std::cout << (this->isInvalid ? "\033[31m❯ \033[0m" : "❯ ");
  std::cin >> option;

  return option;
}

void Platform::menu() {
  std::cout << "1. Cargar archivo de datos" << std::endl
            << "3. Buscar video" << std::endl
            << "4. Buscar serie" << std::endl
            << "5. Buscar pelicula" << std::endl
            << "6. Calificar video\n\n";

  char option = this->getOption();
  this->isInvalid = false;

  this->clear();
  this->showTitle();

  switch (option) {
  case '1':
    this->loadFile();
    break;
  case '2':
    std::cout << "Buscar video" << std::endl;
    std::cin.ignore();
    break;
  case '3':
    std::cout << "Buscar serie" << std::endl;
    std::cin.ignore();
    break;
  case '4':
    std::cout << "Buscar pelicula" << std::endl;
    std::cin.ignore();
    break;
  case '5':
    std::cout << "Calificar video" << std::endl;
    std::cin.ignore();
  default:
    this->isInvalid = true;
    break;
  }
}

void Platform::loadFile() {
  std::string path;

  std::cout << "Cargar archivo de datos\n\n";
  std::cout << "Ingrese la direccion del archivo: ";

  std::cin.ignore();
  std::getline(std::cin, path);

  std::cout << "path: " << path << std::endl;
  std::cin.ignore();
}

void Platform::showTitle() {
  std::cout << "\033[34m======\033[0m " << title
            << " \033[34m======\033[0m\n\n";
}

void Platform::clear() { std::system("clear"); }