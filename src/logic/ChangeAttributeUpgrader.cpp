#include "ChangeAttributeUpgrader.hpp"
#include "UnitToken.hpp"


ChangeAttributeUpgrader::ChangeAttributeUpgrader(Module* module, AttributeName name, int changeValue, bool affectsEnemies)
  : Upgrader(module, affectsEnemies), attributeToChange(name), changeValue(changeValue) {
}

void ChangeAttributeUpgrader::upgrade(BoardToken* token)
{
  Attribute* attribute = token -> getAttribute(attributeToChange);
  if (attribute != NULL) {
    attribute -> upgradeBy(changeValue);
    return;
  }
  UnitToken* unit = dynamic_cast<UnitToken*>(token);
  if (unit != NULL) {
    for (int i=0; i<6; ++i) {
      Attributes* sideAttributes = unit -> getEdgeAttributes(Side(i));
      Attribute* toUpgrade;
      if (sideAttributes != NULL) {
        toUpgrade = sideAttributes -> getAttribute(attributeToChange);
        if (toUpgrade != NULL) {
          toUpgrade -> upgradeBy(changeValue);
        }
      }
    }
  }
}

void ChangeAttributeUpgrader::downgrade(BoardToken* token)
{
  Attribute* attribute = token -> getAttribute(attributeToChange);
  if (attribute != NULL) {
    attribute -> downgradeBy(changeValue);
    return;
  }
  UnitToken* unit = dynamic_cast<UnitToken*>(token);
  if (unit != NULL) {
    for (int i=0; i<6; ++i) {
      Attributes* sideAttributes = unit -> getEdgeAttributes(Side(i));
      Attribute* toUpgrade;
      if (sideAttributes != NULL) {
        toUpgrade = sideAttributes -> getAttribute(attributeToChange);
        if (toUpgrade != NULL) {
          toUpgrade -> downgradeBy(changeValue);
        }
      }
    }
  }
}
