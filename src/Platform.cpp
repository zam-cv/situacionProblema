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
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

static const int LOAD_ERROR_OPTIONS_SIZE = 2;
static const int MENU_OPTIONS_SIZE = 7;
static const int FILE_LOAD_OPTIONS_SIZE = 2;
static const std::string TITLE = "Plataforma de Streaming";
static const std::string DEFAULT_DATA_FILE_PATH = "../DatosPeliculas.csv";

Platform::Platform() {
  this->menuOptions = new Option[MENU_OPTIONS_SIZE]{
      {"Cargar archivo de datos", [&]() { this->loadFile(); }},
      {"Buscar video", [&]() { this->searchVideo(); }},
      {"Buscar serie", [&]() { this->searchSerie(); }},
      {"Buscar pelicula", [&]() { this->searchMovie(); }},
      {"Calificar video", [&]() { this->rateVideo(); }},
      {"Promedio de la serie", [&]() { this->seriesAverage(); }},
      {"Salir", [&]() { exit(0); }}};

  this->fileLoadOptions = new Option[FILE_LOAD_OPTIONS_SIZE]{
      {"Intentar nuevamente", [&]() { this->loadFile(); }},
      {"Regresar al Menu", [&]() { this->menu(); }}};

  this->loadErrorOptions = new Option[LOAD_ERROR_OPTIONS_SIZE]{
      {"Cargar archivo", [&]() { this->loadFile(); }},
      {"Regresar al Menu", [&]() { this->menu(); }}};

  this->genresVec = std::vector<std::string>();

  this->seriesDict = ContentsDict();
  this->videos = std::vector<Video *>();
  this->movies = std::vector<Movie *>();

  this->isInvalid = false;
  this->uploadedFiles = false;
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

    int optionInt = String::toInt(optionStr);
    optionInt--;

    if (optionInt >= 0 && optionInt < size) {
      option = optionInt;
      break;
    }

    this->isInvalid = true;
  }

  this->isInvalid = false;
  this->showTitle();
  handlers[option].handle();
}

void Platform::menu() {
  this->showOptions([]() { std::cout << Font::bold("Menu\n\n"); },
                    this->menuOptions, MENU_OPTIONS_SIZE);
}

void Platform::loadFile() {
  std::string path;

  std::cout << Font::bold("Carga del archivo de datos") << "\n\n";
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
        []() {
          std::cout << Color::red("Error al abrir el archivo") << "\n\n";
        },
        this->fileLoadOptions, FILE_LOAD_OPTIONS_SIZE);
  } else {
    std::set<std::string> genresSet;
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
      std::string name = String::trim(row[1]);
      const std::string durationStr = row[2];
      const std::vector<std::string> genres =
          String::split(String::trim(row[3]), '&');
      const std::string ratingStr = row[4];
      const std::string releaseDate = row[5];

      int duration = std::stod(durationStr);
      double rating = std::stoi(ratingStr);

      std::vector<std::string> words =
          String::split(String::toLower(name), ' ');

      for (std::string genre : genres) {
        genresSet.insert(genre);
      }

      if (row.size() == 7) {
        Movie *movie =
            new Movie(id, name, duration, genres, rating, releaseDate);
        movies.push_back(movie);
      } else if (row.size() == 10) {
        const std::string idEpisode = row[6];
        const std::string nameEpisode = row[7];
        const std::string seasonNumberStr = row[8];
        const std::string episodeNumberStr = row[9];

        int seasonNumber = std::stoi(seasonNumberStr);
        int episodeNumber = std::stoi(episodeNumberStr);

        Video video(idEpisode, nameEpisode, duration, genres, rating,
                    releaseDate);
        Episode *episode = new Episode(video, seasonNumber, episodeNumber);

        if (series.find(name) == series.end()) {
          std::vector<Season *> seasons;
          std::vector<Episode *> episodes;

          episodes.push_back(episode);

          Season *season = new Season(episodes, seasonNumber);
          seasons.push_back(season);

          Serie *serie = new Serie(id, name, genres, seasons);

          std::unordered_map<int, Season *> seasonsHash;
          seasonsHash[seasonNumber] = season;

          series[name] = {serie, seasonsHash};

          if (words.size() > 1) {
            for (std::string word : words) {
              if (word.size() > 2) {
                seriesDict[word].push_back(serie);
              }
            }
          } else {
            seriesDict[name].push_back(serie);
          }
        } else {
          if (series[name].second.find(seasonNumber) ==
              series[name].second.end()) {
            std::vector<Episode *> episodes;

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

    this->genresVec =
        std::vector<std::string>(genresSet.begin(), genresSet.end());

    std::sort(this->movies.begin(), this->movies.end(), [](Video *a, Video *b) {
      return a->getRating() < b->getRating();
    });

    std::cout << std::endl;

    std::cout << Color::green("Los datos se han cargado correctamente");
    std::cout << "\nPresione enter para regresar al menu...";

    this->uploadedFiles = true;
    std::cin.ignore();
  }
}

void Platform::checkUploadedFiles(std::function<void()> next) {
  if (this->uploadedFiles) {
    next();
    return;
  }

  this->showOptions(
      []() {
        std::cout << Color::red("No se ha cargado ningun archivo") << "\n\n";
      },
      this->loadErrorOptions, LOAD_ERROR_OPTIONS_SIZE);
}

Content *Platform::search(ContentsDict *dict, std::string name) {
  std::unordered_map<std::string, std::pair<int, Content *>> coincidences;
  std::vector<std::string> words = String::split(String::toLower(name), ' ');

  for (std::string word : words) {
    if (dict->find(word) != dict->end()) {
      for (Content *content : (*dict)[word]) {
        if (coincidences.find(content->getName()) == coincidences.end()) {
          coincidences[content->getName()] = {1, content};
        } else {
          coincidences[content->getName()].first++;
        }
      }
    }
  }

  Content *content = nullptr;

  if (coincidences.size() > 0) {
    int max = 0;

    for (auto const &coincidence : coincidences) {
      if (coincidence.second.first > max) {
        max = coincidence.second.first;
        content = coincidence.second.second;
      }
    }
  }

  return content;
}

void Platform::searchVideo() {
  this->checkUploadedFiles([]() {
    std::cout << "Buscar video\n\n";
    std::cin.ignore();
  });
}

void Platform::searchSerie() {
  this->checkUploadedFiles([&]() {
    std::string name;

    std::cout << Font::bold("Buscar serie") << "\n\n";
    std::cout << "Ingrese el nombre de la serie: ";

    std::cin.ignore();
    std::getline(std::cin, name);

    Content *content = this->search(&this->seriesDict, name);

    std::cout << std::endl;

    if (content != nullptr) {
      std::cout << content->toString() << "\n\n";
    } else {
      std::cout << Color::red("No se encontro la serie") << "\n\n";
    }

    std::cout << "\nPresione enter para regresar al menu...";
    std::cin.ignore();

    this->menu();
  });
}

void Platform::searchMovie() {
  this->checkUploadedFiles([&]() {
    std::string ratingStr;

    std::cout << Font::bold("Buscar peliculas") << "\n\n";
    std::cout
        << "Se daran las peliculas cuya calificación sea mayor a la ingresada"
        << std::endl;
    std::cout << "Ingrese la calificación: ";

    std::cin.ignore();
    std::getline(std::cin, ratingStr);

    double rating = String::toDouble(ratingStr);

    int start = 0;
    int end = this->movies.size() - 1;

    while (start <= end) {
      int mid = (start + end) / 2;

      if (this->movies[mid]->getRating() == rating) {
        start = mid;
        break;
      } else if (this->movies[mid]->getRating() > rating) {
        start = mid + 1;
      } else {
        end = mid - 1;
      }
    }

    std::cout << std::endl;

    if (start <= this->movies.size() - 1) {
      for (int i = this->movies.size() - 1; i >= start; i--) {
        std::cout << this->movies[i]->toString() << "\n";
      }
    } else {
      std::cout << Color::yellow("No se encontraron coincidencias\n");
    }

    std::cout << "\nPresione enter para regresar al menu...";
    std::cin.ignore();

    this->menu();
  });
}

void Platform::rateVideo() {
  this->checkUploadedFiles([]() {
    std::cout << "Calificar video\n\n";
    std::cin.ignore();
  });
}

void Platform::seriesAverage() {
  this->checkUploadedFiles([&]() {
    std::string name;

    std::cout << Font::bold("Calcular promedio de la serie") << "\n\n";
    std::cout << "Ingrese el nombre de la serie: ";

    std::cin.ignore();
    std::getline(std::cin, name);

    Content *content = this->search(&this->seriesDict, name);

    std::cout << std::endl;

    if (content != nullptr) {
      std::cout << Color::green("Su promedio es: " +
                                Number::withPrecision(content->getRating(), 1))
                << "\n\n";
      std::cout << content->toString() << std::endl;
    } else {
      std::cout << Color::red("No se encontro la serie") << "\n\n";
    }

    std::cout << "\nPresione enter para regresar al menu...";
    std::cin.ignore();

    this->menu();
  });
}

void Platform::showTitle() {
  this->clear();
  std::cout << Color::blue("====== ") << Font::bold(TITLE) << " "
            << Color::blue("====== ") << "\n\n";
}

void Platform::clear() { std::cout << "\033[2J\033[1;1H"; }