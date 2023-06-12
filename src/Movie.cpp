#include <string>
#include <vector>

#include "./include/Movie.h"
#include "./include/Video.h"

#include "./include/Utils.h"

Movie::Movie(Video video) : Video(video) {}

Movie::Movie(std::string id, std::string name, int duration,
             std::vector<std::string> genres, double rating,
             std::string releaseDate)
    : Video(id, name, duration, genres, rating, releaseDate) {}

std::string Movie::toString() { return Color::blue("⦿ ") + Video::toString(); }