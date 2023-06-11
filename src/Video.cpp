#include "./include/Video.h"
#include "./include/Content.h"

#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>

Video::Video(std::string id, std::string name, int duration, std::string genres,
             double rating, std::string releaseDate)
    : Content(id, name) {
  this->releaseDate = releaseDate;
  this->genres = genres;
  this->rating = rating;
  this->duration = duration;
}

std::string Video::toString() {
  std::stringstream stream;
  stream << std::fixed << std::setprecision(2) << this->rating;
  std::string ratingStr = stream.str();

  return this->name + " (" + this->releaseDate + ") " + this->genres + " " +
         ratingStr + " " + std::to_string(this->duration) + " min";
}
