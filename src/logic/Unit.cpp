#include "Unit.hpp"

Unit::Unit(Army army, std::string name, Attributes* attributes, Attributes** sideAttributes)
  : BoardToken(army, name, attributes) {
  this->side = sideAttributes;
}

Attributes* Unit::getSideAttributes(Side side) {
  return this->side[side];
}
