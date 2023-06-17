#ifndef SERIE_H
#define SERIE_H

#include "Content.h"
#include "Season.h"

#include <string>
#include <vector>
#include <set>

class Serie : public Content {
private:
  std::vector<Season *> seasons;

public:
  Serie(std::string id, std::string name, std::set<std::string> genres,
        std::vector<Season *> seasons);
  std::string toString() override;
  double getRating() override;
  void setRating(double rating) override;
  void pushSeason(Season *season);
};

#endif