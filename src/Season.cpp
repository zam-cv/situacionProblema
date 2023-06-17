#include <string>
#include <vector>

#include "./include/Episode.h"
#include "./include/Season.h"

#include "./include/Utils.h"

// Se declara el constructor de la clase Season por defecto
Season::Season() {
  this->seasonNumber = 0;
  this->episodes = {};
}

// Se declara el constructor de la clase Season con atributos necesarios
Season::Season(std::vector<Episode *> episodes, int seasonNumber) {
  this->seasonNumber = seasonNumber;
  this->episodes = episodes;
}

// Metodo para colocar un episodio en la temporada
void Season::pushEpisode(Episode *episode) { this->episodes.push_back(episode); }

// Metodo para pasar a string la clase Season
std::string Season::toString() {
  std::string episodes = "";

  for (int i = 0; i < this->episodes.size(); i++) {
    episodes += "    " + this->episodes[i]->toString();

    if (i != this->episodes.size() - 1) {
      episodes += "\n";
    }
  }

  return Color::yellow("  ⦿") +
         Font::bold(" Temporada " + std::to_string(this->seasonNumber)) + "\n" +
         episodes;
}

// Metodo para obtener el rating de la temporada
double Season::getRating() {
  double rating = 0;

  // Se recorre el vector de episodios y se suma el rating de cada uno
  for (int i = 0; i < this->episodes.size(); i++) {
    rating += this->episodes[i]->getRating();
  }

  // Se retorna el rating promedio de la temporada
  return rating / this->episodes.size();
}

// Metodo para colocar un rating a la temporada
void Season::setRating(double rating) {
  // Se recorre el vector de episodios y se coloca el rating a cada uno
  for (int i = 0; i < this->episodes.size(); i++) {
    this->episodes[i]->setRating(rating);
  }
}