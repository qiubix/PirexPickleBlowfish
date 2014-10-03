#include "UnitToken.hpp"

UnitToken::UnitToken(Army army, std::string name, Attributes* attributes)
  : BoardToken(army, name, attributes),
    edges({{Side::NORTH, nullptr},{Side::NORTH_EAST, nullptr},{Side::NORTH_WEST, nullptr},
          {Side::SOUTH, nullptr},{Side::SOUTH_EAST, nullptr},{Side::SOUTH_WEST, nullptr},})
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

