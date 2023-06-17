#include "./include/Content.h"

// Se declara el constructor de la clase Content
Content::Content(std::string id, std::string name) {
  this->id = id;
  this->name = name;
}

// Metodo para obtener el nombre del contenido
std::string Content::getName() { return this->name; }

// Metodo para saber si el contenido tiene un cierto genero
bool Content::findGenre(std::string genre) {
  // Se busca el genero en el set de generos
  if (this->genres.find(genre) != this->genres.end()) {
    return true;
  }

  return false;
}

// Destructor de la clase Content
Content::~Content() { }