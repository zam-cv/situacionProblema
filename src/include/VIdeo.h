#ifndef VIDEO_H
#define VIDEO_H

#include <string>
#include <vector>

class Video {
private:
  int id;
  std::string name;
  std::vector<std::string> genres;
  double rating;           // 1 to 7
  int duration;            // in minutes
  std::string releaseDate; // mm/dd/aaaa

public:
  Video(int id, std::string name, std::string genres, double rating,
        int duration, std::string releaseDate);
  std::string toString();
};

#endif