#include "BoardToken.hpp"

BoardToken::BoardToken() {
  this->field = 0;
}

BoardToken::BoardToken(std::map<std::string, Attribute *> attributes) {
  this->attributes = attributes;
  this->field = 0;
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
