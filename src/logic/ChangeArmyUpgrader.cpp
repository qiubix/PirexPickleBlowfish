#include "ChangeArmyUpgrader.hpp"

ChangeArmyUpgrader::ChangeArmyUpgrader(Module* module)
  : Upgrader(module), newArmyValue(module->getArmy()) {
}

void ChangeArmyUpgrader::upgrade(BoardToken* token) {
  token->setArmy(newArmyValue);
}

void ChangeArmyUpgrader::downgrade(BoardToken* token) {
  token->resetArmy();
}
