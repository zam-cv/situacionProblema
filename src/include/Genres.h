#ifndef GENRES_H
#define GENRES_H

#include <string>
#include <vector>

class Genres {
private:
  std::vector<std::string> genres;

public:
  Genres();
  Genres(std::string);
  std::vector<std::string> getGenres();
  std::string toString();
};

#endif