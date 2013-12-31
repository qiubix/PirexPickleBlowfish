#include "BoardToken.hpp"

BoardToken::BoardToken() {
  this->field = 0;
}

Field* BoardToken::getField() {
  return field;
}

Attribute* BoardToken::getAttribute(std::string name) {
  return attributes[name];
}
