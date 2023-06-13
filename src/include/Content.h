#ifndef CONTENT_H
#define CONTENT_H

#include <string>
#include <vector>

class Content {
protected:
  std::string id;
  std::string name;

public:
  Content(std::string id, std::string name);
  std::string getName();
  virtual double getRating() = 0;
  virtual std::string toString() = 0;
  virtual ~Content();
};

#endif