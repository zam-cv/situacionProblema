#include "./include/Episode.h"
#include "./include/Video.h"
#include <string>

Episode::Episode(Video video, int seasonNumber, int episodeNumber)
    : Video(video) {
  this->seasonNumber = seasonNumber;
  this->episodeNumber = episodeNumber;
}

std::string Episode::toString() {
  return "\033[34m⦿\033[0m " + Video::toString();
}