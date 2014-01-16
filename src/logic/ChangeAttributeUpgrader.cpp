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
  try {
    throw token;
  }
  catch(UnitToken* unit) {
    for (int i=0; i<6; ++i) {
      Attributes* sideAttributes = unit->getEdgeAttributes(Side(i));
      Attribute* toUpgrade = sideAttributes->getAttribute(attributeToChange);
      if (toUpgrade != NULL) {
        attribute->upgrade(changeValue);
      }
    }
  }
  catch(std::exception ex) {
    //..
  }
}
//  else if (static_cast<UnitToken>(token).getEdgeAttributes(NORTH) != NULL) {
  //TODO: upgrade edge attribute
//  }

void ChangeAttributeUpgrader::downgrade(BoardToken* token)
{
  Attribute* attribute = token->getAttribute(attributeToChange);
  if (attribute != NULL) {
    attribute->downgrade(changeValue);
  }
  //TODO: downgrade edge attribute
  try {
    throw token;
  }
  catch(UnitToken* unit) {
    for (int i=0; i<6; ++i) {
      Attributes* sideAttributes = unit->getEdgeAttributes(Side(i));
      Attribute* toUpgrade = sideAttributes->getAttribute(attributeToChange);
      if (toUpgrade != NULL) {
        attribute->downgrade(changeValue);
      }
    }
  }
  catch(std::exception ex) {
    //..
  }
}
