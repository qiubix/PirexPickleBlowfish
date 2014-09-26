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
	int index = static_cast <int> (edge);
	if ( edges[index] == NULL) {
		edges[index] = new Attributes;
	}
	return edges[index];
}

void UnitToken::setEdgeAttributes(Side edge, Attributes* attributes)
{
	edges[static_cast <int> (edge)] = attributes;
}

