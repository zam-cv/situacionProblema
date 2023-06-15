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
      {"Buscar videos", [&]() { this->searchVideo(); }},
      {"Buscar serie", [&]() { this->searchSerie(); }},
      {"Buscar peliculas", [&]() { this->searchMovie(); }},
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
  this->videosDict = ContentsDict();
  this->episodesList = std::vector<Content *>();
  this->moviesList = std::vector<Content *>();

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
    std::getline(std::cin, optionStr);

    int optionInt = String::toInt(optionStr) - 1;

    if (Number::isBetween(optionInt, -1, size)) {
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

  std::getline(std::cin, path);

  if (path.empty())
    path = DEFAULT_DATA_FILE_PATH;

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
        if (!token.empty() && token != "\r")
          row.push_back(token);
        line.erase(0, pos + delimiter.length());
      }

      row.push_back(line);

      const std::string id = row[0];
      std::string name = String::trim(row[1]);
      const std::string durationStr = row[2];
      const std::vector<std::string> genres =
          String::split(String::trim(String::replace(row[3], "' ", "&")), '&');
      const std::string ratingStr = row[4];
      const std::string releaseDate = row[5];

      int duration = String::toInt(durationStr);
      double rating = String::toDouble(ratingStr);

      for (std::string genre : genres) {
        genresSet.insert(genre);
      }

      if (row.size() == 7) {
        Movie *movie =
            new Movie(id, name, duration, genres, rating, releaseDate);
        this->moviesList.push_back(movie);
        this->setWords(&this->videosDict, name, movie);
      } else if (row.size() == 10) {
        const std::string idEpisode = row[6];
        const std::string nameEpisode = row[7];
        const std::string seasonNumberStr = row[8];
        const std::string episodeNumberStr = row[9];

        int seasonNumber = String::toInt(seasonNumberStr);
        int episodeNumber = String::toInt(episodeNumberStr);

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

          this->setWords(&seriesDict, name, serie);
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
            this->setWords(&this->videosDict, nameEpisode, episode);
            this->episodesList.push_back(episode);
          }
        }
      }
    }

    this->genresVec =
        std::vector<std::string>(genresSet.begin(), genresSet.end());

    std::sort(
        this->moviesList.begin(), this->moviesList.end(),
        [](Content *a, Content *b) { return a->getRating() > b->getRating(); });
    std::sort(
        this->episodesList.begin(), this->episodesList.end(),
        [](Content *a, Content *b) { return a->getRating() > b->getRating(); });

    std::cout << std::endl;

    std::cout << Color::green("Los datos se han cargado correctamente");
    this->uploadedFiles = true;

    std::cout << "\nPresione enter para regresar al menu...";
    std::cin.ignore();
  }
}

void Platform::setWords(ContentsDict *dict, std::string name,
                        Content *content) {
  name = String::toLower(name);
  std::vector<std::string> words = String::split(name, ' ');

  if (words.size() > 1) {
    for (std::string word : words) {
      if (word.size() > 2)
        (*dict)[word].push_back(content);
    }
  } else {
    (*dict)[name].push_back(content);
  }
}

void Platform::checkUploadedFiles(std::function<void()> next) {
  if (this->uploadedFiles) {
    next();

    std::cout << "\nPresione enter para regresar al menu...";
    std::cin.ignore();
    this->menu();

    return;
  }

  this->showOptions(
      []() {
        std::cout << Color::red("No se ha cargado ningun archivo") << "\n\n";
      },
      this->loadErrorOptions, LOAD_ERROR_OPTIONS_SIZE);
}

std::vector<Content *> Platform::search(std::vector<Content *> *vec,
                                        double rating) {
  std::vector<Content *> contents;

  for (Content *content : *vec) {
    if (content->getRating() >= rating)
      contents.push_back(content);
  }

  return contents;
}

Content *Platform::search(ContentsDict *dict, std::string name) {
  std::unordered_map<std::string, std::pair<int, Content *>> coincidences;
  std::vector<std::string> words = String::split(String::toLower(name), ' ');

  for (std::string word : words) {
    if (dict->find(word) != dict->end()) {
      for (Content *content : (*dict)[word]) {
        std::string contentName = String::toLower(content->getName());
        if (coincidences.find(contentName) == coincidences.end()) {
          coincidences[contentName] = {1, content};
        } else {
          coincidences[contentName].first++;
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
  this->checkUploadedFiles([&]() {
    int genresPerLine = 7;
    std::string ratingStr;
    std::string genreStr;

    std::cout << Font::bold("Buscar video") << "\n\n";
    std::cout
        << "Se daran las peliculas cuya calificación sea mayor a la ingresada."
        << std::endl;
    std::cout << "Tambien se daran las peliculas que coincidan con el genero "
                 "ingresado."
              << "\n\n";

    std::cout << "Ingrese la calificación: ";
    std::getline(std::cin, ratingStr);

    std::cout << std::endl << Font::bold("Generos disponibles: ") << "\n\n";

    for (int i = 0; i < this->genresVec.size(); i++) {
      std::cout << i + 1 << ". " << this->genresVec[i] << "  ";

      if ((i + 1) % genresPerLine == 0)
        std::cout << std::endl;
    }

    if (this->genresVec.size() % genresPerLine != 0)
      std::cout << std::endl;

    std::cout << std::endl << "Ingrese el genero: ";
    std::getline(std::cin, genreStr);

    int genreInt = String::toInt(genreStr) - 1;
    std::cout << std::endl;

    if (Number::isBetween(genreInt, -1, this->genresVec.size())) {
      std::string genre = this->genresVec[genreInt];
      double rating = String::toDouble(ratingStr);

      std::vector<Content *> movies = this->search(&this->moviesList, rating);
      std::vector<Content *> episodes = this->search(&this->episodesList, rating);

      int count = 0;

      for (Content *content : movies) {
        if (content->findGenre(genre)) {
          std::cout << content->toString() << std::endl;
          count++;
        }
      }

      for (Content *content : episodes) {
        if (content->findGenre(genre)) {
          Movie vid = *(Movie *)(content);
          std::cout << vid.toString() << std::endl;
          count++;
        }
      }

      if (count == 0) {
        std::cout << Color::red("No se encontraron videos") << std::endl;
      }
    } else {
      std::cout << Color::red("La opcion ingresada no es valida") << std::endl;
    }
  });
}

void Platform::searchSerie() {
  this->checkUploadedFiles([&]() {
    std::string name;

    std::cout << Font::bold("Buscar serie") << "\n\n";
    std::cout << "Ingrese el nombre de la serie: ";

    std::getline(std::cin, name);

    Content *content = this->search(&this->seriesDict, name);

    std::cout << std::endl;

    if (content != nullptr) {
      std::cout << content->toString() << std::endl;
    } else {
      std::cout << Color::red("No se encontro la serie") << std::endl;
    }
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

    std::getline(std::cin, ratingStr);
    double rating = String::toDouble(ratingStr);

    std::vector<Content *> moviesChunk =
        this->search(&this->moviesList, rating);
    std::cout << std::endl;

    if (moviesChunk.size() > 0) {
      for (Content *content : moviesChunk) {
        std::cout << content->toString() << std::endl;
      }
    } else {
      std::cout << Color::yellow("No se encontraron coincidencias")
                << std::endl;
    }
  });
}

void Platform::rateVideo() {
  this->checkUploadedFiles([&]() {
    std::string name;
    std::string ratingStr;

    std::cout << Font::bold("Calificar video") << "\n\n";

    std::cout << "Ingrese el nombre del video: ";
    std::getline(std::cin, name);

    std::cout << "Ingrese la calificación: ";
    std::getline(std::cin, ratingStr);

    double rating = String::toDouble(ratingStr);

    Content *content = this->search(&this->videosDict, name);

    std::cout << std::endl;

    if (content != nullptr) {
      if (rating >= 0 && rating <= 10) {
        content->setRating(rating);
        std::cout << content->toString() << "\n\n";
        std::cout << Color::green("Se califico el video correctamente")
                  << std::endl;
      } else {
        std::cout << Color::red("La calificación debe estar entre 0 y 10")
                  << std::endl;
      }
    } else {
      std::cout << Color::red("No se encontro el video") << std::endl;
    }
  });
}

void Platform::seriesAverage() {
  this->checkUploadedFiles([&]() {
    std::string name;

    std::cout << Font::bold("Calcular promedio de la serie") << "\n\n";
    std::cout << "Ingrese el nombre de la serie: ";
    std::getline(std::cin, name);

    Content *content = this->search(&this->seriesDict, name);

    std::cout << std::endl;

    if (content != nullptr) {
      std::cout << Color::green("Su promedio es: " +
                                Number::withPrecision(content->getRating(), 1))
                << "\n\n";
      std::cout << content->toString() << std::endl;
    } else {
      std::cout << Color::red("No se encontro la serie") << std::endl;
    }
  });
}

void Platform::showTitle() {
  this->clear();
  std::cout << Color::blue("====== ") << Font::bold(TITLE) << " "
            << Color::blue("====== ") << "\n\n";
}

void Platform::clear() { std::cout << "\033[2J\033[1;1H"; }