#include "Attributes.hpp"

Attribute* Attributes::getAttribute(AttributeName name)
{
  return attributes[name];
}

void Attributes::addAttribute(AttributeName name, Attribute* attribute)
{
  attributes.insert(std::make_pair<AttributeName, Attribute*>(name, attribute));
}
