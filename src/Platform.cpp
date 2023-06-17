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

// Constantes
static const int LOAD_ERROR_OPTIONS_SIZE = 2;
static const int MENU_OPTIONS_SIZE = 7;
static const int FILE_LOAD_OPTIONS_SIZE = 2;
static const std::string TITLE = "Plataforma de Streaming";
static const std::string DEFAULT_DATA_FILE_PATH = "../DatosPeliculas.csv";

Platform::Platform() {
  // Opciones del menú
  this->menuOptions = new Option[MENU_OPTIONS_SIZE]{
      {"Cargar archivo de datos", [&]() { this->loadFile(); }},
      {"Buscar videos", [&]() { this->searchVideo(); }},
      {"Buscar serie", [&]() { this->searchSerie(); }},
      {"Buscar películas", [&]() { this->searchMovie(); }},
      {"Calificar video", [&]() { this->rateVideo(); }},
      {"Promedio de la serie", [&]() { this->seriesAverage(); }},
      {"Salir", [&]() { exit(0); }}};

  // Opciones de carga de archivo
  this->fileLoadOptions = new Option[FILE_LOAD_OPTIONS_SIZE]{
      {"Intentar nuevamente", [&]() { this->loadFile(); }},
      {"Regresar al Menú", [&]() { this->menu(); }}};

  // Opciones de error de carga de archivo
  this->loadErrorOptions = new Option[LOAD_ERROR_OPTIONS_SIZE]{
      {"Cargar archivo", [&]() { this->loadFile(); }},
      {"Regresar al Menú", [&]() { this->menu(); }}};

  // Generos existentes
  this->genresVec = std::vector<std::string>();

  // Estrucutras de datos para almacenar los videos
  this->seriesDict = ContentsDict();
  this->videosDict = ContentsDict();
  this->episodesList = std::vector<Content *>();
  this->moviesList = std::vector<Content *>();

  // Variables de control
  this->isInvalid = false;
  this->uploadedFiles = false;
}

void Platform::run() {
  // Itera indefinidamente el menu
  while (true) {
    this->showTitle();
    this->menu();
  }
}

// Metodo para mostrar las opciones
void Platform::showOptions(std::function<void()> showMessage, Option *handlers,
                           int size) {
  int option;

  while (true) {
    this->showTitle();
    // Muestra el mensaje de la funcion showMessage
    showMessage();

    // Muestra las opciones
    for (int i = 0; i < size; i++)
      std::cout << Font::bold(Number::toStr(i + 1) + ". ") << handlers[i].name
                << std::endl;

    std::cout << std::endl;
    if (this->isInvalid) {
      std::cout << Color::red("Opción inválida") << std::endl;
    }

    // Pide la opcion al usuario
    std::string optionStr =
        Console::input(this->isInvalid ? Color::red("❯ ") : "❯ ");
    // Convierte la opcion a entero
    int optionInt = String::toInt(optionStr) - 1;

    // Verifica que este entre el rango de opciones
    if (Number::isBetween(optionInt, -1, size)) {
      option = optionInt;
      break;
    }

    // Si no esta en el rango, se muestra un mensaje de error
    this->isInvalid = true;
  }

  this->isInvalid = false;
  this->showTitle();
  // Se ejecuta la funcion correspondiente a la opcion
  handlers[option].handle();
}

// Metodo para mostrar el menú
void Platform::menu() {
  this->showOptions([]() { std::cout << Font::bold("Menú\n\n"); },
                    this->menuOptions, MENU_OPTIONS_SIZE);
}

// Metodo para cargar el archivo de datos
void Platform::loadFile() {
  std::cout << Font::bold("Carga del archivo de datos") << "\n\n";
  std::cout << "Archivo a usar si se presiona enter: " << DEFAULT_DATA_FILE_PATH
            << std::endl;
  // Pide la direccion del archivo
  std::string path = Console::input("Ingrese la dirección del archivo: ");

  // Si no se ingresa nada, se usa la direccion por defecto
  if (path.empty())
    path = DEFAULT_DATA_FILE_PATH;

  std::ifstream file(path);

  // Se comprueba que el archivo exista
  if (!file.is_open()) {
    this->showOptions(
        []() {
          std::cout << Color::red("Error al abrir el archivo") << "\n\n";
        },
        this->fileLoadOptions, FILE_LOAD_OPTIONS_SIZE);
  } else {
    // Estructura para recolectar todos los generos existentes
    std::set<std::string> genresSet;
    // Estructura para recolectar los episodios de las series con sus temporadas
    std::unordered_map<std::string,
                       std::pair<Serie *, std::unordered_map<int, Season *>>>
        series;
    std::string line;
    std::getline(file, line);

    // Se lee el archivo linea por linea
    while (std::getline(file, line)) {
      std::set<std::string> currentGenresSet;

      // Se separa la linea por comas
      std::vector<std::string> row;

      std::string delimiter = ",";
      size_t pos = 0;
      std::string token;

      while ((pos = line.find(delimiter)) != std::string::npos) {
        token = line.substr(0, pos);
        // Se agrega el token a la fila si no esta vacio
        if (!token.empty() && token != "\r")
          row.push_back(token);
        line.erase(0, pos + delimiter.length());
      }

      // Se agrega el ultimo token a la fila
      row.push_back(line);

      // Se obtienen los datos de la fila
      const std::string id = row[0];
      std::string name = String::trim(row[1]);
      const std::string durationStr = row[2];
      const std::vector<std::string> genres =
          String::split(String::trim(String::replace(row[3], "' ", "&")), '&');
      const std::string ratingStr = row[4];
      const std::string releaseDate = row[5];

      // Se convierten los datos a los tipos correspondientes
      int duration = String::toInt(durationStr);
      double rating = String::toDouble(ratingStr);

      // Se agregan los generos a la lista de generos
      for (std::string genre : genres) {
        genresSet.insert(genre);
        currentGenresSet.insert(genre);
      }

      // Se comprueba si es una serie o una pelicula
      if (row.size() == 7) {
        // Se crea la pelicula
        Movie *movie = new Movie(id, name, duration, currentGenresSet, rating,
                                 releaseDate);

        // Se agrega la pelicula a la lista de peliculas y al diccionario de
        // videos
        this->moviesList.push_back(movie);
        this->setWords(&this->videosDict, name, movie);
      } else if (row.size() == 10) {
        // Se obtienen los datos del episodio
        const std::string idEpisode = row[6];
        const std::string nameEpisode = row[7];
        const std::string seasonNumberStr = row[8];
        const std::string episodeNumberStr = row[9];

        // Se convierten los datos a los tipos correspondientes
        int seasonNumber = String::toInt(seasonNumberStr);
        int episodeNumber = String::toInt(episodeNumberStr);

        // Se crea el video y el episodio
        Video video(idEpisode, nameEpisode, duration, currentGenresSet, rating,
                    releaseDate);
        Episode *episode = new Episode(video, seasonNumber, episodeNumber);

        // Se verifica si la serie ya existe
        if (series.find(name) == series.end()) { // Si la serie no existe
          // Se crea la serie con la temporada y el episodio correspondiente
          // Se agregan los datos a las estructuras
          std::vector<Season *> seasons;
          std::vector<Episode *> episodes;

          episodes.push_back(episode);

          Season *season = new Season(episodes, seasonNumber);
          seasons.push_back(season);

          Serie *serie = new Serie(id, name, currentGenresSet, seasons);

          std::unordered_map<int, Season *> seasonsHash;
          seasonsHash[seasonNumber] = season;

          series[name] = {serie, seasonsHash};

          this->setWords(&seriesDict, name, serie);
        } else { // Si la serie ya existe
          // Se verifica si la temporada ya existe
          if (series[name].second.find(seasonNumber) ==
              series[name].second.end()) { // Si la temporada no existe
            // Se crea la temporada con el episodio correspondiente
            std::vector<Episode *> episodes;

            episodes.push_back(episode);

            Season *season = new Season(episodes, seasonNumber);

            series[name].second[seasonNumber] = season;
            series[name].first->pushSeason(season);
          } else { // Si la temporada ya existe
            // Se agrega el episodio a la temporada
            series[name].second[seasonNumber]->pushEpisode(episode);
            this->setWords(&this->videosDict, nameEpisode, episode);
            this->episodesList.push_back(episode);
          }
        }
      }
    }

    // Se convierte el set de generos a un vector
    this->genresVec =
        std::vector<std::string>(genresSet.begin(), genresSet.end());

    // Se ordenan las listas de peliculas y episodios por rating
    std::sort(
        this->moviesList.begin(), this->moviesList.end(),
        [](Content *a, Content *b) { return a->getRating() > b->getRating(); });
    std::sort(
        this->episodesList.begin(), this->episodesList.end(),
        [](Content *a, Content *b) { return a->getRating() > b->getRating(); });

    std::cout << Color::green("\nLos datos se han cargado correctamente");
    this->uploadedFiles = true;

    Console::pause("\nPresione enter para regresar al menú...");
  }
}

// Coloca las palabras de un nombre en el diccionario con el contenido
void Platform::setWords(ContentsDict *dict, std::string name,
                        Content *content) {
  name = String::toLower(name);
  std::vector<std::string> words = String::split(name, ' ');

  if (words.size() > 1) { // Si el nombre tiene mas de una palabra
    // Se agregan las palabras al diccionario
    for (std::string word : words) {
      // La palabra debe tener mas de 2 caracteres
      if (word.size() > 2)
        (*dict)[word].push_back(content);
    }
  } else { // Si el nombre tiene una sola palabra
    (*dict)[name].push_back(content);
  }
}

// Comprueba si se han cargado los archivos
void Platform::checkUploadedFiles(std::function<void()> next) {
  if (this->uploadedFiles) {
    // Se ejecuta la funcion
    next();
    Console::pause("\nPresione enter para regresar al menú...");
    this->menu();

    return;
  }

  this->showOptions(
      []() {
        std::cout << Color::red("No se ha cargado ningún archivo") << "\n\n";
      },
      this->loadErrorOptions, LOAD_ERROR_OPTIONS_SIZE);
}

// Busca un contenido por rating
std::vector<Content *> Platform::search(std::vector<Content *> *vec,
                                        double rating) {
  std::vector<Content *> contents;

  // Se recorre el vector de contenidos
  for (Content *content : *vec) {
    // Se verifica si el rating del contenido es mayor o igual al rating dado
    if (content->getRating() >= rating)
      contents.push_back(content);
  }

  return contents;
}

// Busca un contenido por nombre
Content *Platform::search(ContentsDict *dict, std::string name) {
  std::unordered_map<std::string, std::pair<int, Content *>> coincidences;
  std::vector<std::string> words = String::split(String::toLower(name), ' ');

  // Se recorren las palabras del nombre
  for (std::string word : words) {
    // Se verifica si la palabra esta en el diccionario
    if (dict->find(word) != dict->end()) {
      // Se recorren los contenidos de la palabra
      for (Content *content : (*dict)[word]) {
        std::string contentName = String::toLower(content->getName());
        // Se verifica si el contenido no esta en el mapa de coincidencias
        if (coincidences.find(contentName) == coincidences.end()) {
          // Se agrega el contenido al mapa de coincidencias
          coincidences[contentName] = {1, content};
        } else {
          // Se aumenta el contador de coincidencias
          coincidences[contentName].first++;
        }
      }
    }
  }

  Content *content = nullptr;

  // Se verifica si hay coincidencias
  if (coincidences.size() > 0) {
    int max = 0;

    // Se busca la coincidencia con mayor cantidad de palabras
    for (auto const &coincidence : coincidences) {
      if (coincidence.second.first > max) {
        max = coincidence.second.first;
        content = coincidence.second.second;
      }
    }
  }

  return content;
}

// Busca un video
void Platform::searchVideo() {
  this->checkUploadedFiles([&]() {
    int genresPerLine = 7; // Generos por linea al imprimir

    std::cout << Font::bold("Buscar video") << "\n\n";
    std::cout
        << "Se daran las películas cuya calificación sea mayor a la ingresada."
        << std::endl;
    std::cout << "También se daran las películas que coincidan con el género "
                 "ingresado."
              << "\n\n";

    std::string ratingStr = Console::input("Ingrese la calificación: ");
    std::cout << std::endl << Font::bold("Géneros disponibles: ") << "\n\n";

    // Se imprimen los generos
    for (int i = 0; i < this->genresVec.size(); i++) {
      std::cout << Font::bold(Number::toStr(i + 1) + ". ") << this->genresVec[i]
                << "  ";

      if ((i + 1) % genresPerLine == 0)
        std::cout << std::endl;
    }

    // Se imprime un salto de linea si no se imprimieron todos los generos
    if (this->genresVec.size() % genresPerLine != 0)
      std::cout << std::endl;

    std::string genreStr = Console::input("\nIngrese el género: ");

    int genreInt = String::toInt(genreStr) - 1;
    std::cout << std::endl;

    // Se verifica si el genero esta en el rango
    if (Number::isBetween(genreInt, -1, this->genresVec.size())) {
      // Se obtiene el genero seleccionado
      std::string genre = this->genresVec[genreInt];
      double rating = String::toDouble(ratingStr);

      // Se buscan los contenidos
      std::vector<Content *> movies = this->search(&this->moviesList, rating);
      std::vector<Content *> episodes =
          this->search(&this->episodesList, rating);

      int count = 0;

      // Se imprimen los contenidos que coincidan con el genero
      for (Content *content : movies) {
        if (content->findGenre(genre)) {
          std::cout << content->toString() << std::endl;
          count++;
        }
      }

      for (Content *content : episodes) {
        if (content->findGenre(genre)) {
          Movie mov = *(Movie *)(content);
          std::cout << mov.toString() << std::endl;
          count++;
        }
      }

      if (count == 0)
        std::cout << Color::red("No se encontraron videos") << std::endl;
    } else {
      std::cout << Color::red("La opción ingresada no es válida") << std::endl;
    }
  });
}

// Busca una serie
void Platform::searchSerie() {
  this->checkUploadedFiles([&]() {
    std::cout << Font::bold("Buscar serie") << "\n\n";
    std::string name = Console::input("Ingrese el nombre de la serie: ");

    // Se busca la serie por nombre
    Content *content = this->search(&this->seriesDict, name);
    std::cout << std::endl;

    // Se verifica si se encontro la serie
    if (content != nullptr) {
      std::cout << Color::green("Serie con más coincidencias") << "\n\n";
      std::cout << content->toString() << std::endl;
    } else {
      std::cout << Color::red("No se encontró la serie") << std::endl;
    }
  });
}

// Busca una pelicula
void Platform::searchMovie() {
  this->checkUploadedFiles([&]() {
    std::cout << Font::bold("Buscar películas") << "\n\n";
    std::cout
        << "Se daran las películas cuya calificación sea mayor a la ingresada"
        << std::endl;

    std::string ratingStr = Console::input("Ingrese la calificación: ");
    double rating = String::toDouble(ratingStr);

    // Se buscan las peliculas por rating
    std::vector<Content *> moviesChunk =
        this->search(&this->moviesList, rating);
    std::cout << std::endl;

    // Si se encontraron peliculas se imprimen
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

// Califica un video
void Platform::rateVideo() {
  this->checkUploadedFiles([&]() {
    std::cout << Font::bold("Calificar video") << "\n\n";
    std::string name = Console::input("Ingrese el nombre del video: ");
    std::string ratingStr = Console::input("Ingrese la calificación: ");

    double rating = String::toDouble(ratingStr);

    // Se busca el video por nombre
    Content *content = this->search(&this->videosDict, name);
    std::cout << std::endl;

    // Se verifica si se encontro el video
    if (content != nullptr) {
      // Se verifica si el rating esta en el rango
      if (rating >= 0 && rating <= 10) {
        // Se coloca el nuevo rating
        content->setRating(rating);
        std::cout << content->toString() << "\n\n";
        std::cout << Color::green("Se calificó el video correctamente")
                  << std::endl;
      } else {
        std::cout << Color::red("La calificación debe estar entre 0 y 10")
                  << std::endl;
      }
    } else {
      std::cout << Color::red("No se encontró el video") << std::endl;
    }
  });
}

// Calcula el promedio de una serie
void Platform::seriesAverage() {
  this->checkUploadedFiles([&]() {
    std::cout << Font::bold("Calcular promedio de la serie") << "\n\n";
    std::string name = Console::input("Ingrese el nombre de la serie: ");

    // Se busca la serie por nombre
    Content *content = this->search(&this->seriesDict, name);
    std::cout << std::endl;

    // Se verifica si se encontro la serie
    if (content != nullptr) {
      std::cout << Color::green("Su promedio es: " +
                                Number::withPrecision(content->getRating(), 1))
                << "\n\n";
      std::cout << content->toString() << std::endl;
    } else {
      std::cout << Color::red("No se encontró la serie") << std::endl;
    }
  });
}

// Muestra el titulo de la plataforma
void Platform::showTitle() {
  this->clear();
  std::cout << Color::blue("====== ") << Font::bold(TITLE) << " "
            << Color::blue("====== ") << "\n\n";
}

// Limpia la consola
void Platform::clear() { std::cout << "\033[2J\033[1;1H"; }