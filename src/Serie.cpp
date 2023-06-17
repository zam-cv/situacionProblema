#include <string>
#include <set>

#include "./include/Content.h"
#include "./include/Season.h"
#include "./include/Serie.h"

#include "./include/Utils.h"

// Se declara el constructor de la clase Serie con atributos necesarios
Serie::Serie(std::string id, std::string name, std::set<std::string> genres,
             std::vector<Season *> seasons)
    : Content(id, name) {

  this->genres = genres;
  this->seasons = seasons;
}

// Metodo para pasar a string la clase Serie
std::string Serie::toString() {
  std::string seasonsStr = "";

  for (int i = 0; i < this->seasons.size(); i++) {
    seasonsStr += this->seasons[i]->toString();

    if (i != this->seasons.size() - 1) {
      seasonsStr += "\n";
    }
  }

  return Color::red("⦿ ") + Font::bold(this->name) + Color::magenta(" • ") +
         Font::italic(String::join(this->genres, ' ')) + "\n" + seasonsStr;
}

// Metodo para colocar una temporada en la serie
void Serie::pushSeason(Season *season) { this->seasons.push_back(season); }

// Metodo para obtener el rating de la serie
double Serie::getRating() {
  double rating = 0;

  // Se recorre el vector de temporadas y se suma el rating de cada una
  for (int i = 0; i < this->seasons.size(); i++) {
    rating += this->seasons[i]->getRating();
  }

  // Se retorna el rating promedio de la serie
  return rating / this->seasons.size();
}

// Metodo para colocar un rating a la serie
void Serie::setRating(double rating) {
  // Se recorre el vector de temporadas y se coloca el rating a cada una
  for (int i = 0; i < this->seasons.size(); i++) {
    this->seasons[i]->setRating(rating);
  }
}