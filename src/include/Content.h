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
  virtual std::string toString() = 0;
};

#endif