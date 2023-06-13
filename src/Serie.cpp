#include <string>

#include "./include/Content.h"
#include "./include/Season.h"
#include "./include/Serie.h"

#include "./include/Utils.h"

Serie::Serie(std::string id, std::string name, std::vector<std::string> genres,
             std::vector<Season *> seasons)
    : Content(id, name) {
  this->genres = genres;
  this->seasons = seasons;
}

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

void Serie::pushSeason(Season *season) { this->seasons.push_back(season); }

double Serie::getRating() {
  double rating = 0;

  for (int i = 0; i < this->seasons.size(); i++) {
    rating += this->seasons[i]->getRating();
  }

  return rating / this->seasons.size();
}

void Serie::setRating(double rating) {
  for (int i = 0; i < this->seasons.size(); i++) {
    this->seasons[i]->setRating(rating);
  }
}

bool Serie::findGenre(std::string genre) {
  for (int i = 0; i < this->genres.size(); i++) {
    if (this->genres[i] == genre) {
      return true;
    }
  }

  return false;
}