#include "ChangeArmyUpgrader.hpp"

ChangeArmyUpgrader::ChangeArmyUpgrader(Module* module)
  : Upgrader(module), newArmyValue(module->getArmy()) {}

void ChangeArmyUpgrader::upgrade(BoardToken* token)
{
  Attribute* armyAttribute = token->getAttribute(ARMY);
  if (armyAttribute != NULL) {
    armyAttribute->upgradeTo(newArmyValue);
  }
}

void ChangeArmyUpgrader::downgrade(BoardToken* token)
{
  Attribute* armyAttribute = token->getAttribute(ARMY);
  if (armyAttribute != NULL) {
    armyAttribute->downgradeTo();
  }

}
