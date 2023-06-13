#include <string>
#include <vector>

#include "./include/Episode.h"
#include "./include/Season.h"

#include "./include/Utils.h"

Season::Season() {
  this->seasonNumber = 0;
  this->episodes = {};
}

Season::Season(std::vector<Episode *> episodes, int seasonNumber) {
  this->seasonNumber = seasonNumber;
  this->episodes = episodes;
}

void Season::pushEpisode(Episode *episode) { this->episodes.push_back(episode); }

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

double Season::getRating() {
  double rating = 0;

  for (int i = 0; i < this->episodes.size(); i++) {
    rating += this->episodes[i]->getRating();
  }

  return rating / this->episodes.size();
}

void Season::setRating(double rating) {
  for (int i = 0; i < this->episodes.size(); i++) {
    this->episodes[i]->setRating(rating);
  }
}