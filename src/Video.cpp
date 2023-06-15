#include "./include/Video.h"
#include "./include/Content.h"

#include "./include/Utils.h"

#include <iostream>
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
  return Font::bold(this->name) + " " + Color::gray(this->releaseDate) +
         Color::magenta(" • ") + Font::italic(String::join(this->genres, ' ')) +
         Color::magenta(" • ") + Number::withPrecision(this->rating, 1) +
         Color::magenta(" • ") + std::to_string(this->duration) + " min";
}

double Video::getRating() { return this->rating; }

void Video::setRating(double rating) { this->rating = rating; }

bool Video::findGenre(std::string genre) {
  for (int i = 0; i < this->genres.size(); i++) {
    if (this->genres[i] == genre) {
      return true;
    }
  }

  return false;
}