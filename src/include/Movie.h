#ifndef MOVIE_H
#define MOVIE_H

#include "Video.h"
#include <string>
#include <vector>

class Movie : public Video {
public:
  Movie(Video video);
  Movie(std::string id, std::string name, int duration,
        std::vector<std::string> genres, double rating,
        std::string releaseDate);
  std::string toString() override;
};

#endif