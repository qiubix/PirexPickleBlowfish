#include "Attributes.hpp"

Attributes::Attributes(void) {
}

Attributes::~Attributes(void) {
  std::map<AttributeName, Attribute*>::iterator iterator;
  for(iterator = attributes.begin(); iterator != attributes.end(); iterator++) {
    delete iterator->second;
  }
}

Attribute* Attributes::getAttribute(AttributeName name) {
  //TODO: use attributes.at(name) instead of []
  std::map<AttributeName, Attribute*>::iterator it = attributes.find(name);
  if(it != attributes.end()) {
    return attributes[name];
  }
  else {
    return NULL;
  }
}

int Attributes::getSize()
{
  return attributes.size();
}

void Attributes::addAttribute(AttributeName name, Attribute* attribute) {
  attributes.insert(std::make_pair<AttributeName, Attribute*>(name, attribute));
}

void Attributes::removeAttribute(AttributeName name) {
  attributes.erase(attributes.find(name));
}
