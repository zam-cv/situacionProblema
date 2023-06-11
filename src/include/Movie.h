#ifndef MOVIE_H
#define MOVIE_H

#include "Content.h"
#include "Video.h"
#include <string>

class Movie : public Video {
public:
  Movie(std::string id, std::string name, int duration, std::string genres,
        double rating, std::string releaseDate);
  std::string toString();
};

#endif