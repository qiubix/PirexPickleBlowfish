#include "ChangeArmyUpgrader.hpp"

ChangeArmyUpgrader::ChangeArmyUpgrader(Module* module, bool affectsEnemies)
  : Upgrader(module, affectsEnemies), newArmyValue(module->getArmy()) {
}

void ChangeArmyUpgrader::upgrade(BoardToken* token) {
  token->setArmy(newArmyValue);
}

void ChangeArmyUpgrader::downgrade(BoardToken* token) {
  token->resetArmy();
}
