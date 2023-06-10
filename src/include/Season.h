#ifndef SEASON_H
#define SEASON_H

#include "Episode.h"

#include <vector>

class Season {
private:
  int seasonNumber;
  std::vector<Episode> episodes;

public:
  Season(std::vector<Episode> episodes, int seasonNumber);
  std::vector<Episode> getEpisodes();
  int getSeasonNumber();
  void pushEpisode(Episode episode);
  std::string toString();
};

#endif