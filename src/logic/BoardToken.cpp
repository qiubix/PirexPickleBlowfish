#include "BoardToken.hpp"

BoardToken::BoardToken(Attributes* attributes)
{
  this->field = NULL;
  this->orientation = NORTH;
  this->attributes = attributes;
}

BoardToken::~BoardToken(void) {
  delete attributes;
}

Field* BoardToken::getField(void) {
  return field;
}

void BoardToken::setField(Field* field) {
  this->field = field;
}

Attribute* BoardToken::getAttribute(AttributeName name) {
  return attributes->getAttribute(name);
}

void BoardToken::upgradeAttribute(AttributeName name) {
  getAttribute(name)->upgradeAttribute();
}

void BoardToken::downgradeAttribute(AttributeName name) {
  getAttribute(name)->downgradeAttribute();
}

Side BoardToken::getOrientation(void) {
  return orientation;
}

void BoardToken::setOrientation(Side orientation) {
  this->orientation = orientation;
}

void BoardToken::rotateClockwise(void)
{
  int newSide = orientation;
  newSide = (++newSide)%6;
  orientation = static_cast<Side>(newSide);
}

void BoardToken::rotateAntiClockwise(void)
{
  int newSide = orientation;
  if (--newSide == -1) {
    newSide = 5;
  }
  orientation = static_cast<Side>(newSide);
}
