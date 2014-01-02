#include "Attribute.hpp"

Attribute::Attribute(std::string name, int baseValue) {
  this->name = name;
  this->baseValue = baseValue;
  this->currentValue = baseValue;
}

std::string Attribute::getName(void) {
  return name;
}

int Attribute::getValue(void) {
  return currentValue;
}

void Attribute::upgradeAttribute(void) {
  ++currentValue;
}

void Attribute::downgradeAttribute(void) {
  --currentValue;
}
