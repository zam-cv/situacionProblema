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