#ifndef MOVIE_H
#define MOVIE_H

#include "Video.h"

class Movie : public Video {
private:
public:
  Movie(Video video);
  std::string toString();
};

#endif