#include "ChangeAttributeUpgrader.hpp"
#include "UnitToken.hpp"


ChangeAttributeUpgrader::ChangeAttributeUpgrader(Module* module, AttributeName name, int changeValue)
  : Upgrader(module), attributeToChange(name), changeValue(changeValue) {}

void ChangeAttributeUpgrader::upgrade(BoardToken* token)
{
  Attribute* attribute = token->getAttribute(attributeToChange);
  if (attribute != NULL) {
    attribute->upgrade(changeValue);
  }
//  else if (static_cast<UnitToken>(token).getEdgeAttributes(NORTH) != NULL) {
  //TODO: upgrade edge attribute
//  }
}

void ChangeAttributeUpgrader::downgrade(BoardToken* token)
{

}
