#include "HeadquartersToken.hpp"


HeadQuartersToken::HeadQuartersToken(Army army, std::string name, Attributes* attributes, Attributes** edges)
  : UnitToken(army, name, attributes, edges), ModuleToken(army, name, attributes) {}
