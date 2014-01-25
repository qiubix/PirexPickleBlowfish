#include "HeadquartersToken.hpp"


HeadQuartersToken::HeadQuartersToken(Army army, std::string name, Attributes* attributes, std::vector<Side> edges)
  : UnitToken(army, name, attributes), ModuleToken(army, name, attributes, edges) {}
