#ifndef PLATFORM_H
#define PLATFORM_H

#include <string>

struct Option {
  std::string name;
  std::function<void()> handle;
};

class Platform {
private:
  // loadErrorOptions
  static const int LOAD_ERROR_OPTIONS_SIZE = 2;
  static const int MENU_OPTIONS_SIZE = 6;
  static const int FILE_LOAD_OPTIONS_SIZE = 2;

  Option *menuOptions;
  Option *fileLoadOptions;
  Option *loadErrorOptions;

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
  void checkUploadedFiles();

public:
  Platform();
  void run();
};

#endif