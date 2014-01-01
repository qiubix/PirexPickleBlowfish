#include "BoardToken.hpp"

BoardToken::BoardToken() {
  this->field = 0;
  this->rotation = new Attribute("rotation", NORTH);
  this->attributes.insert(std::make_pair<std::string, Attribute*>(rotation->getName(), rotation));
}

BoardToken::BoardToken(std::map<std::string, Attribute *> attributes) {
  this->attributes = attributes;
  this->field = 0;
  std::map<std::string, Attribute*>::iterator it = attributes.find("rotation");
  if (it != attributes.end()) {
    this->rotation = it->second;
  } else {
    this->rotation = new Attribute("rotation", NORTH);
    this->attributes.insert(std::make_pair<std::string, Attribute*>(rotation->getName(), rotation));
  }
}

Field* BoardToken::getField() {
  return field;
}

void BoardToken::setField(Field* field) {
  this->field = field;
}

Attribute* BoardToken::getAttribute(std::string name) {
  return attributes[name];
}

void BoardToken::addAttribute(Attribute *attribute) {
  attributes.insert(std::make_pair<std::string, Attribute*>(attribute->getName(), attribute));
}

Orientation BoardToken::getRotation() {
  return static_cast<Orientation>(rotation->getUpgradedValue());
}
