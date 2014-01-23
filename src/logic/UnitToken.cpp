#include "UnitToken.hpp"

UnitToken::UnitToken(Army army, std::string name, Attributes* attributes)
  : BoardToken(army, name, attributes) {
  edges = new Attributes*[6];
  for (int i=0; i<6; i++) {
    edges[i] = NULL;
  }
}

UnitToken::~UnitToken()
{
  for (int i=0; i<6; i++) {
    if(edges[i] != NULL) {
      delete edges[i];
    }
  }
  delete[] edges;
}

Attributes* UnitToken::getEdgeAttributes(Side edge) {
  return this->edges[edge];
}

void UnitToken::setEdgeAttributes(Side edge, Attributes* attributes)
{
  edges[edge] = attributes;
}

