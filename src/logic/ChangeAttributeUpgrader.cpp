#include "ChangeAttributeUpgrader.hpp"
#include "UnitToken.hpp"


ChangeAttributeUpgrader::ChangeAttributeUpgrader(Module* module, AttributeName name, int changeValue, bool affectsEnemies)
  : Upgrader(module, affectsEnemies), attributeToChange(name), changeValue(changeValue) {
}

void ChangeAttributeUpgrader::upgrade(BoardToken* token)
{
  Attribute* attribute = token -> getAttribute(attributeToChange);
  if (attribute != nullptr) {
    attribute -> upgradeBy(changeValue);
    return;
  }
  UnitToken* unit = dynamic_cast<UnitToken*>(token);
  if (unit != nullptr) {
    for (int i=0; i<6; ++i) {
      Attributes* sideAttributes = unit -> getEdgeAttributes(Side(i));
      Attribute* toUpgrade;
      if (sideAttributes != nullptr) {
        toUpgrade = sideAttributes -> getAttribute(attributeToChange);
        if (toUpgrade != nullptr) {
          toUpgrade -> upgradeBy(changeValue);
        }
      }
    }
  }
}

void ChangeAttributeUpgrader::downgrade(BoardToken* token)
{
  Attribute* attribute = token -> getAttribute(attributeToChange);
  if (attribute != nullptr) {
    attribute -> downgradeBy(changeValue);
    return;
  }
  UnitToken* unit = dynamic_cast<UnitToken*>(token);
  if (unit != nullptr) {
    for (int i=0; i<6; ++i) {
      Attributes* sideAttributes = unit -> getEdgeAttributes(Side(i));
      Attribute* toUpgrade;
      if (sideAttributes != nullptr) {
        toUpgrade = sideAttributes -> getAttribute(attributeToChange);
        if (toUpgrade != nullptr) {
          toUpgrade -> downgradeBy(changeValue);
        }
      }
    }
  }
}

AttributeName ChangeAttributeUpgrader::getAttributeToChange() const{
  return attributeToChange;
}

int ChangeAttributeUpgrader::getChangeValue() const {
  return changeValue;
}