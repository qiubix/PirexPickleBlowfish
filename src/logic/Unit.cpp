#include "Unit.hpp"

Unit::Unit(Army army, std::string name, Attributes* attributes, Attributes** sideAttributes)
  : BoardToken(army, name, attributes) {
  this->side = sideAttributes;
}

//REVIEW: maybe edge is better name?
Attributes* Unit::getSideAttributes(Side side) {
  return this->side[side];
}
