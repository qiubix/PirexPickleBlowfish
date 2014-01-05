#include "UnitToken.hpp"

UnitToken::UnitToken(Army army, std::string name, Attributes* attributes, Attributes** edgeAttributes)
  : BoardToken(army, name, attributes) {
  this->edges = edgeAttributes;
}

Attributes* UnitToken::getEdgeAttributes(Side edge) {
  return this->edges[edge];
}
