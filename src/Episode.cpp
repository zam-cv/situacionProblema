#include "./include/Episode.h"
#include "./include/Video.h"

#include "./include/Utils.h"

#include <string>
#include <iostream>

Episode::Episode(Video video, int seasonNumber, int episodeNumber)
    : Video(video) {
  this->seasonNumber = seasonNumber;
  this->episodeNumber = episodeNumber;
}

std::string Episode::toString() {
  return Color::blue("⦿ ") + Font::bold(this->name) + " " +
         Color::gray(this->releaseDate) + Color::magenta(" • ") +
         Number::withPrecision(this->rating, 1) + Color::magenta(" • ") +
         std::to_string(this->duration) + " min";
}