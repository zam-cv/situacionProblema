#include "./include/Video.h"
#include "./include/Content.h"

#include "./include/Utils.h"

#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

Video::Video(std::string id, std::string name, int duration,
             std::vector<std::string> genres, double rating,
             std::string releaseDate)
    : Content(id, name) {
  this->releaseDate = releaseDate;
  this->genres = genres;
  this->rating = rating;
  this->duration = duration;
}

std::string Video::toString() {
  std::stringstream stream;
  stream << std::fixed << std::setprecision(1) << this->rating;
  std::string ratingStr = stream.str();

  return Font::bold(this->name) + " " + Color::gray(this->releaseDate) +
         Color::magenta(" • ") + Font::italic(String::join(this->genres, ' ')) +
         Color::magenta(" • ") + ratingStr + Color::magenta(" • ") +
         std::to_string(this->duration) + " min";
}

double Video::getRating() { return this->rating; }