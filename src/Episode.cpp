#include "./include/Episode.h"
#include "./include/Video.h"

#include "./include/Utils.h"

#include <iomanip>
#include <sstream>
#include <string>

Episode::Episode(Video video, int seasonNumber, int episodeNumber)
    : Video(video) {
  this->seasonNumber = seasonNumber;
  this->episodeNumber = episodeNumber;
}

std::string Episode::toString() {
  std::stringstream stream;
  stream << std::fixed << std::setprecision(1) << this->rating;
  std::string ratingStr = stream.str();

  return Color::blue("    ⦿ ") + Font::bold(this->name) + " " +
         Color::gray(this->releaseDate) + Color::magenta(" • ") + ratingStr +
         Color::magenta(" • ") + std::to_string(this->duration) + " min";
}