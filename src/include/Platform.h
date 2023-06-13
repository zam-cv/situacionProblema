#ifndef PLATFORM_H
#define PLATFORM_H

#include <vector>
#include <string>
#include <unordered_map>

#include "Movie.h"
#include "Serie.h"
#include "Episode.h"
#include "Content.h"

typedef std::unordered_map<std::string, std::vector<Content*>> ContentsDict;

struct Option {
  std::string name;
  std::function<void()> handle;
};

class Platform {
private:
  Option *menuOptions;
  Option *fileLoadOptions;
  Option *loadErrorOptions;

  std::vector<std::string> genresVec;

  std::vector<Content *> episodesList;
  std::vector<Content *> moviesList;
  ContentsDict seriesDict;
  ContentsDict videosDict;

  bool isInvalid;
  bool uploadedFiles;

  void clear();
  void menu();
  void showTitle();
  void showOptions(std::function<void()> showMessage, Option *handlers, int size);
  void loadFile();
  void setWords(ContentsDict *dict, std::string name, Content *content);
  Content* search(ContentsDict *dict, std::string name);
  std::vector<Content *> search(std::vector<Content *> *vec, double rating);
  void searchVideo();
  void searchSerie();
  void searchMovie();
  void rateVideo();
  void seriesAverage();
  void checkUploadedFiles(std::function<void()> next);

public:
  Platform();
  void run();
};

#endif