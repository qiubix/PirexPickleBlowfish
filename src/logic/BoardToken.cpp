#include "BoardToken.hpp"

BoardToken::BoardToken(Army army, std::string name, Attributes* attributes)
  : Token(army, name), attributes(attributes) {
  this -> field = nullptr;
  this -> orientation = Side::NORTH;
  if (attributes == nullptr) {
    this -> attributes = new Attributes;
  }
}

BoardToken::~BoardToken() {
  delete attributes;
}

Attribute* BoardToken::getAttribute(AttributeName name) {
  return attributes -> getAttribute(name);
}

Attributes*BoardToken::getAttributes() {
  return attributes;
}

void BoardToken::addAttribute(AttributeName name, Attribute* attribute) {
  attributes -> addAttribute(name, attribute);
}

void BoardToken::removeAttribute(AttributeName name) {
  attributes -> removeAttribute(name);
}

void BoardToken::upgradeAttributeBy(AttributeName name, int upgradeValue) {
  getAttribute(name) -> upgradeBy(upgradeValue);
}

void BoardToken::downgradeAttributeBy(AttributeName name, int downgradeValue) {
  getAttribute(name) -> downgradeBy(downgradeValue);
}

void BoardToken::rotateClockwise() {
  ++orientation;
}

void BoardToken::rotateAnticlockwise() {
  --orientation;
}

Field * BoardToken::getField() {
  return field;
}

Side BoardToken::getOrientation() {
  return orientation;
}

void BoardToken::setArmy(Army army) {
  this -> army -> upgradeTo(army);
}

void BoardToken::resetArmy() {
  this->army->resetValue();
}

void BoardToken::setField(Field* field) {
  this -> field = field;
}

void BoardToken::setOrientation(Side orientation) {
  this -> orientation = orientation;
}
