#include "BoardToken.hpp"

BoardToken::BoardToken() {
  this->field = 0;
}

BoardToken::BoardToken(std::map<std::string, Attribute *> attributes) {
  this->attributes = attributes;
}

Field* BoardToken::getField() {
  return field;
}

Attribute* BoardToken::getAttribute(std::string name) {
  return attributes[name];
}
