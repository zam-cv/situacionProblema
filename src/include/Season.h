#ifndef SEASON_H
#define SEASON_H

#include "Episode.h"

#include <string>
#include <vector>

class Season {
private:
  int seasonNumber;
  std::vector<Episode> episodes;

public:
  Season();
  Season(std::vector<Episode> episodes, int seasonNumber);
  void pushEpisode(Episode episode);
  std::string toString();
};

#endif