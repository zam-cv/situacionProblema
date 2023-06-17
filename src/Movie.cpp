#include <string>
#include <vector>
#include <set>

#include "./include/Movie.h"
#include "./include/Video.h"

#include "./include/Utils.h"

// Se declara el constructor de la clase Movie con un objeto de la clase Video
Movie::Movie(Video video) : Video(video) {}

// Se declara el constructor de la clase Movie con atributos necesarios
Movie::Movie(std::string id, std::string name, int duration,
             std::set<std::string> genres, double rating,
             std::string releaseDate)
    : Video(id, name, duration, genres, rating, releaseDate) {}

// Metodo para pasar a string la clase Movie
std::string Movie::toString() { return Color::blue("⦿ ") + Video::toString(); }