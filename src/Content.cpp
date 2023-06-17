#include "./include/Content.h"

Content::Content(std::string id, std::string name) {
  this->id = id;
  this->name = name;
}

std::string Content::getName() { return this->name; }

bool Content::findGenre(std::string genre) {
  if (this->genres.find(genre) != this->genres.end()) {
    return true;
  }

  return false;
}

Content::~Content() { }