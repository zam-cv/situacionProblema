#ifndef PLATFORM_H
#define PLATFORM_H

#include <vector>
#include <string>
#include <unordered_map>

#include "Movie.h"
#include "Serie.h"
#include "Episode.h"

struct Option {
  std::string name;
  std::function<void()> handle;
};

class Platform {
private:
  static const int LOAD_ERROR_OPTIONS_SIZE = 2;
  static const int MENU_OPTIONS_SIZE = 6;
  static const int FILE_LOAD_OPTIONS_SIZE = 2;

  Option *menuOptions;
  Option *fileLoadOptions;
  Option *loadErrorOptions;

  std::unordered_map<std::string, std::vector<Movie*>> moviesDict;
  std::unordered_map<std::string, std::vector<Serie*>> seriesDict;
  std::unordered_map<std::string, std::vector<Episode*>> episodesDict;

  bool isInvalid;
  bool uploadedFiles;

  void clear();
  void menu();
  void showTitle();
  void showOptions(std::function<void()> showMessage, Option *handlers, int size);
  void loadFile();
  void searchVideo();
  void searchSerie();
  void searchMovie();
  void rateVideo();
  void checkUploadedFiles(std::function<void()> next);

public:
  Platform();
  void run();
};

#endif