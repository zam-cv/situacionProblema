#ifndef CONTENT_H
#define CONTENT_H

#include <string>
#include <vector>
#include <set>

class Content {
protected:
  std::string id;
  std::string name;
  std::set<std::string> genres;

public:
  Content(std::string id, std::string name);
  std::string getName();
  virtual double getRating() = 0;
  virtual std::string toString() = 0;
  virtual void setRating(double rating) = 0;
  virtual bool findGenre(std::string genre);
  virtual ~Content();
};

#endif