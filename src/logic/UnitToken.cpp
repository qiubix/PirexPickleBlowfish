#include "UnitToken.hpp"

UnitToken::UnitToken(Army army, std::string name, Attributes* attributes)
  : BoardToken(army, name, attributes)
{
}

UnitToken::~UnitToken()
{
  for (auto& ed : edges) {
    delete ed.second;
  }
}

Attributes* UnitToken::getEdgeAttributes(const Side& edge) {
  if ( edges[edge] == nullptr) {
    edges[edge] = new Attributes;
  }
  return edges[edge];
}

void UnitToken::setEdgeAttributes(const Side& edge, Attributes* attributes)
{
  edges[edge] = attributes;
}

