#include "./include/Platform.h"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "./include/Video.h"
#include "./include/Movie.h"

static const std::string TITLE = "Plataforma de Streaming";
static const std::string DEFAULT_DATA_FILE_PATH = "../DatosPeliculas.csv";

Platform::Platform() {
  this->menuOptions = new Option[this->MENU_OPTIONS_SIZE]{
      {"Cargar archivo de datos", [&]() { this->loadFile(); }},
      {"Buscar video", [&]() { this->searchVideo(); }},
      {"Buscar serie", [&]() { this->searchSerie(); }},
      {"Buscar pelicula", [&]() { this->searchMovie(); }},
      {"Calificar video", [&]() { this->rateVideo(); }},
      {"Salir", [&]() { exit(0); }}};

  this->fileLoadOptions = new Option[this->FILE_LOAD_OPTIONS_SIZE]{
      {"Intentar nuevamente", [&]() { this->loadFile(); }},
      {"Regresar al Menu", [&]() { this->menu(); }}};

  this->isInvalid = false;
}

void Platform::run() {
  while (true) {
    this->showTitle();
    this->menu();
  }
}

void Platform::showOptions(std::function<void()> showMessage, Option *handlers, int size) {
  std::string optionStr;
  int option;

  while (true) {
    this->showTitle();
    showMessage();

    for (int i = 0; i < size; i++) {
      std::cout << i + 1 << ". " << handlers[i].name << std::endl;
    }

    std::cout << std::endl;
    std::cout << (this->isInvalid ? "\033[31m❯ \033[0m" : "❯ ");
    std::cin >> optionStr;

    try {
      int optionInt = std::stoi(optionStr);
      optionInt--;

      if (optionInt >= 0 && optionInt < size) {
        option = optionInt;
        break;
      }
    } catch (std::invalid_argument const &e) {
    } catch (std::out_of_range const &e) {}

    this->isInvalid = true;
  }

  this->isInvalid = false;
  this->showTitle();
  handlers[option].handle();
}

void Platform::menu() {
  this->showOptions([]() { 
    std::cout << "Menu\n\n"; 
  }, this->menuOptions, this->MENU_OPTIONS_SIZE);
}

void Platform::loadFile() {
  std::string path;

  std::cout << "Carga del archivo de datos\n\n";
  std::cout << "Archivo a usar si se presiona enter: " << DEFAULT_DATA_FILE_PATH
            << std::endl;
  std::cout << "Ingrese la direccion del archivo: ";

  std::cin.ignore();
  std::getline(std::cin, path);

  if (path.empty()) {
    path = DEFAULT_DATA_FILE_PATH;
  }

  std::ifstream file(path);

  if (!file.is_open()) {
    this->showOptions(
        []() { std::cout << "\033[31mError al abrir el archivo\033[0m\n\n"; },
        this->fileLoadOptions, this->FILE_LOAD_OPTIONS_SIZE);
  } else {
    std::string line;
    std::getline(file, line);

    while (std::getline(file, line)) {
      std::vector<std::string> row;

      std::string delimiter = ",";
      size_t pos = 0;
      std::string token;

      while ((pos = line.find(delimiter)) != std::string::npos) {
        token = line.substr(0, pos);

        if (!token.empty() && token != "\r") {
          row.push_back(token);
        }

        line.erase(0, pos + delimiter.length());
      }

      if (row.size() == 6) {
        int duration = std::stod(row[2]);
        double rating = std::stoi(row[4]);

        Movie movie(row[0], row[1], duration, row[3], rating, row[5]);
        std::cout << movie.toString() << std::endl;
      } else if (row.size() == 9) {
        std::cout << "Serie" << std::endl;
      }
    }

    std::cin.ignore();
  }
}

void Platform::searchVideo() {
  std::cout << "Buscar video\n\n";
  std::cin.ignore();
}

void Platform::searchSerie() {
  std::cout << "Buscar serie\n\n";
  std::cin.ignore();
}

void Platform::searchMovie() {
  std::cout << "Buscar pelicula\n\n";
  std::cin.ignore();
}

void Platform::rateVideo() {
  std::cout << "Calificar video\n\n";
  std::cin.ignore();
}

void Platform::showTitle() {
  this->clear();
  std::cout << "\033[34m======\033[0m " << TITLE
            << " \033[34m======\033[0m\n\n";
}

void Platform::clear() { std::system("clear"); }