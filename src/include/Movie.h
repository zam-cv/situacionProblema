#ifndef MOVIE_H
#define MOVIE_H

#include <string>
#include "Video.h"

class Movie : public Video {
private:
public:
  Movie(Video video);
  std::string toString();
};

#endif