#ifndef SERIE_H
#define SERIE_H

#include "Content.h"
#include "Season.h"

#include <string>
#include <vector>

class Serie : public Content {
private:
  std::vector<std::string> genres;
  std::vector<Season *> seasons;

public:
  Serie(std::string id, std::string name, std::vector<std::string> genres,
        std::vector<Season *> seasons);
  std::string toString() override;
  void pushSeason(Season *season);
  std::string getName();
};

#endif