#include "ChangeArmyUpgrader.hpp"

ChangeArmyUpgrader::ChangeArmyUpgrader(Module* module, bool affectsEnemies)
  : Upgrader(module, affectsEnemies) {
}

void ChangeArmyUpgrader::upgrade(BoardToken* token) {
  token -> setArmy(module -> getArmy());
}

void ChangeArmyUpgrader::downgrade(BoardToken* token) {
  token -> resetArmy();
}
