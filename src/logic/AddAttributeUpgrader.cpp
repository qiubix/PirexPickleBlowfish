#include "AddAttributeUpgrader.hpp"

AddAttributeUpgrader::AddAttributeUpgrader(Module* module, AttributeName name, Attribute* attribute)
  : Upgrader(module), newAttributeName(name)
{
  this->newAttribute = attribute;
}

void AddAttributeUpgrader::upgrade(BoardToken* token)
{
  token->addAttribute(newAttributeName, newAttribute);
}


void AddAttributeUpgrader::downgrade(BoardToken* token)
{
  token->removeAttribute(newAttributeName);
}
