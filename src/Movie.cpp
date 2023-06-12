#include "./include/Movie.h"
#include "./include/Video.h"

Movie::Movie(Video video) : Video(video) {}

Movie::Movie(std::string id, std::string name, int duration, std::string genres,
             double rating, std::string releaseDate)
    : Video(id, name, duration, genres, rating, releaseDate) {}

std::string Movie::toString() {
  return "\033[34m⦿\033[0m " + Video::toString();
}