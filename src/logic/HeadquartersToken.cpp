#include "HeadquartersToken.hpp"


HeadquartersToken::HeadquartersToken(Army army, std::string name, Attributes* attributes, std::vector<Side> edges)
  : UnitToken(army, name, attributes), ModuleToken(army, name, attributes, edges) {
  for (int i=0; i<6; ++i) {
    Attributes* edgeAttributes = new Attributes;
    Attribute* melee = new Attribute("melee", 1);
    edgeAttributes->addAttribute(MELEE, melee);
    this -> setEdgeAttributes((Side) i, edgeAttributes);
  }
  Attribute* initiative = new Attribute("initiative", 0);
  this -> UnitToken::addAttribute(INITIATIVE, initiative);
}
