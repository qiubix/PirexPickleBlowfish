#include "Attribute.hpp"

Attribute::Attribute(std::string name, int baseValue) {
  this->name = name;
  this->baseValue = baseValue;
  this->upgradedValue = baseValue;
}

std::string Attribute::getName() {
  return name;
}

int Attribute::getBaseValue() {
  return baseValue;
}

int Attribute::getUpgradedValue() {
  return upgradedValue;
}

//REVIEW: in .hpp file
void Attribute::upgradeAttribute(int newValue)
{
  upgradedValue = newValue;
}
