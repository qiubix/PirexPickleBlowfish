#include "Module.hpp"

Module::Module(Army army, std::string name, Attributes* attributes)
  : BoardToken(army, name, attributes) {}
