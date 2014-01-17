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

void Attribute::upgrade(int amount) {
  if (this->name == "army") {
    currentValue = amount;
  }
  else {
    currentValue += amount;
  }
}

void Attribute::downgrade(int amount) {
  if (this->name == "army") {
    currentValue = baseValue;
  }
  else {
    currentValue -= amount;
  }
}
