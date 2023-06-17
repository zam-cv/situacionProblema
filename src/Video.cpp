#include "./include/Video.h"
#include "./include/Content.h"

#include "./include/Utils.h"

#include <iostream>
#include <string>
#include <set>

// Se declara el constructor de la clase Video con atributos necesarios
Video::Video(std::string id, std::string name, int duration,
             std::set<std::string> genres, double rating,
             std::string releaseDate)
    : Content(id, name) {
  this->releaseDate = releaseDate;
  this->genres = genres;
  this->rating = rating;
  this->duration = duration;
}

// Metodo para pasar a string la clase Video
std::string Video::toString() {
  return Font::bold(this->name) + " " + Color::gray(this->releaseDate) +
         Color::magenta(" • ") + Font::italic(String::join(this->genres, ' ')) +
         Color::magenta(" • ") + Number::withPrecision(this->rating, 1) +
         Color::magenta(" • ") + std::to_string(this->duration) + " min";
}

// Metodo para obtener el rating del video
double Video::getRating() { return this->rating; }

// Metodo para colocar un rating al video
void Video::setRating(double rating) { this->rating = rating; }