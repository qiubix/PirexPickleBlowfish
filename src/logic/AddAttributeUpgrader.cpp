#include "AddAttributeUpgrader.hpp"

AddAttributeUpgrader::AddAttributeUpgrader(Module* module, Attribute* attribute)
  : Upgrader(module)
{
  this->newAttribute = attribute;
}

void AddAttributeUpgrader::upgrade(BoardToken* token)
{
}


void AddAttributeUpgrader::downgrade(BoardToken* token)
{

}
