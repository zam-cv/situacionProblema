#include "./include/Platform.h"
#include "./include/Content.h"
#include "./include/Episode.h"
#include "./include/Movie.h"
#include "./include/Season.h"
#include "./include/Serie.h"
#include "./include/Video.h"

#include "./include/Utils.h"

#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

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

void Platform::showOptions(std::function<void()> showMessage, Option *handlers,
                           int size) {
  std::string optionStr;
  int option;

  while (true) {
    this->showTitle();
    showMessage();

    for (int i = 0; i < size; i++) {
      std::cout << i + 1 << ". " << handlers[i].name << std::endl;
    }

    std::cout << std::endl;
    std::cout << (this->isInvalid ? Color::red("❯ ") : "❯ ");
    std::cin >> optionStr;

    try {
      int optionInt = std::stoi(optionStr);
      optionInt--;

      if (optionInt >= 0 && optionInt < size) {
        option = optionInt;
        break;
      }
    } catch (std::invalid_argument const &e) {
    } catch (std::out_of_range const &e) {
    }

    this->isInvalid = true;
  }

  this->isInvalid = false;
  this->showTitle();
  handlers[option].handle();
}

void Platform::menu() {
  this->showOptions([]() { std::cout << "Menu\n\n"; }, this->menuOptions,
                    this->MENU_OPTIONS_SIZE);
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
        []() { std::cout << Color::red("Error al abrir el archivo") << "\n\n"; },
        this->fileLoadOptions, this->FILE_LOAD_OPTIONS_SIZE);
  } else {
    std::vector<Content *> contents;
    std::unordered_map<std::string,
                       std::pair<Serie *, std::unordered_map<int, Season *>>>
        series;
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

      row.push_back(line);

      const std::string id = row[0];
      const std::string name = String::trim(row[1]);
      const std::string durationStr = row[2];
      const std::vector<std::string> genres = String::split(String::trim(row[3]), '&');
      const std::string ratingStr = row[4];
      const std::string releaseDate = row[5];

      int duration = std::stod(durationStr);
      double rating = std::stoi(ratingStr);

      if (row.size() == 7) {
        contents.push_back(
            new Movie(id, name, duration, genres, rating, releaseDate));
      } else if (row.size() == 10) {
        const std::string idEpisode = row[6];
        const std::string nameEpisode = row[7];
        const std::string seasonNumberStr = row[8];
        const std::string episodeNumberStr = row[9];

        int seasonNumber = std::stoi(seasonNumberStr);
        int episodeNumber = std::stoi(episodeNumberStr);

        Video video(idEpisode, nameEpisode, duration, genres, rating,
                    releaseDate);
        Episode episode(video, seasonNumber, episodeNumber);

        if (series.find(name) == series.end()) {
          std::vector<Season *> seasons;
          std::vector<Episode> episodes;

          episodes.push_back(episode);

          Season *season = new Season(episodes, seasonNumber);
          seasons.push_back(season);

          Serie *serie = new Serie(id, name, genres, seasons);
          contents.push_back(serie);

          std::unordered_map<int, Season *> seasonsHash;
          seasonsHash[seasonNumber] = season;

          series[name] = {serie, seasonsHash};
        } else {
          if (series[name].second.find(seasonNumber) ==
              series[name].second.end()) {
            std::vector<Episode> episodes;

            episodes.push_back(episode);

            Season *season = new Season(episodes, seasonNumber);

            series[name].second[seasonNumber] = season;
            series[name].first->pushSeason(season);
          } else {
            series[name].second[seasonNumber]->pushEpisode(episode);
          }
        }
      }
    }

    for (Content *content : contents) {
      std::cout << content->toString() << std::endl;
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
  std::cout << Color::blue("====== ") << TITLE << " "
            << Color::blue("====== ") << "\n\n";
}

void Platform::clear() { 
  std::cout << "\033[2J\033[1;1H";
}