#include "./include/Episode.h"
#include "./include/Video.h"

#include "./include/Utils.h"

#include <string>
#include <iostream>

// Se declara el constructor de la clase Episode
Episode::Episode(Video video, int seasonNumber, int episodeNumber)
    : Video(video) {
  this->seasonNumber = seasonNumber;
  this->episodeNumber = episodeNumber;
}

// Metodo para pasar a string la clase Episode
std::string Episode::toString() {
  return Color::blue("⦿ ") + Font::bold(this->name) + " " +
         Color::gray(this->releaseDate) + Color::magenta(" • ") +
         Number::withPrecision(this->rating, 1) + Color::magenta(" • ") +
         std::to_string(this->duration) + " min";
}