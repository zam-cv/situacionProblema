#include "./include/Content.h"

Content::Content(std::string id, std::string name) {
  this->id = id;
  this->name = name;
}

std::string Content::getName() { return this->name; }

Content::~Content() { }