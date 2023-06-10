#ifndef EPISODE_H
#define EPISODE_H

#include "Video.h"
#include <string>

class Episode : public Video {
private:
  int seasonNumber;
  int episodeNumber;

public:
  Episode(int seasonNumber, int episodeNumber, Video video);
  std::string toString();
};

#endif