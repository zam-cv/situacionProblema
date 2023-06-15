#ifndef VIDEO_H
#define VIDEO_H

#include "Content.h"

#include <string>
#include <vector>

class Video : public Content {
protected:
  std::vector<std::string> genres;
  double rating;           // 1 to 7
  int duration;            // in minutes
  std::string releaseDate; // mm/dd/aaaa

public:
  Video(std::string id, std::string name, int duration,
        std::vector<std::string> genres, double rating,
        std::string releaseDate);
  virtual std::string toString() override;
  double getRating() override;
  void setRating(double rating) override;
  bool findGenre(std::string genre) override;
};

#endif