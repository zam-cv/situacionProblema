#ifndef EPISODE_H
#define EPISODE_H

#include "Video.h"
#include <string>

class Episode : public Video {
private:
  int seasonNumber;
  int episodeNumber;

public:
  Episode(Video video, int seasonNumber, int episodeNumber);
  std::string toString() override;
};

#endif