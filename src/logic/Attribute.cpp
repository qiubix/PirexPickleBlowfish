#include "Attribute.hpp"

Attribute::Attribute(std::string name, int baseValue)
  : name(name), baseValue(baseValue){
  this->currentValue = baseValue;
}

std::string Attribute::getName(void) {
  return name;
}

int Attribute::getValue(void) {
  return currentValue;
}

void Attribute::upgradeBy(int amount) {
  currentValue += amount;
}

void Attribute::downgradeBy(int amount) {
  currentValue -= amount;
}

void Attribute::upgradeTo(int newValue) {
  currentValue = newValue;
}

void Attribute::resetValue(void) {
  currentValue = baseValue;
}

void Attribute::downgradeTo(int newValue) {
  currentValue = newValue;
}
