#include "BoardToken.hpp"

BoardToken::BoardToken(Army army, std::string name, Attributes* attributes)
  : Token(army, name), attributes(attributes) {
  this->field = NULL;
  this->orientation = NORTH;
}

BoardToken::~BoardToken(void) {
  delete attributes;
}

Attribute* BoardToken::getAttribute(AttributeName name) {
  return attributes->getAttribute(name);
}

void BoardToken::addAttribute(AttributeName name, Attribute* attribute)
{
  attributes->addAttribute(name, attribute);
}

void BoardToken::upgradeAttribute(AttributeName name) {
  getAttribute(name)->upgrade();
}

void BoardToken::downgradeAttribute(AttributeName name) {
  getAttribute(name)->downgrade();
}

void BoardToken::rotateClockwise(void)
{
  int newOrientation = orientation;
  ++newOrientation %= 6;
  orientation = static_cast<Side>(newOrientation);
}

void BoardToken::rotateAnticlockwise(void)
{
  int newOrientation = orientation;
  if (--newOrientation == -1) {
    newOrientation = 5;
  }
  orientation = static_cast<Side>(newOrientation);
}

Field* BoardToken::getField(void) {
  return field;
}

Side BoardToken::getOrientation(void) {
  return orientation;
}

void BoardToken::setField(Field* field) {
  this->field = field;
}

void BoardToken::setOrientation(Side orientation) {
  this->orientation = orientation;
}
