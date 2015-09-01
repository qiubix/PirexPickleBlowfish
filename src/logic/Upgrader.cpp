#include "Upgrader.hpp"

Upgrader::Upgrader(Module* module, bool affectsEnemies)
  : Module(module->getArmy(), module->getName(), module -> getAttributes()), affectsEnemies(affectsEnemies) {
  this -> module = module;
}

Upgrader::~Upgrader() {
  delete module;
}

void Upgrader::upgrade(BoardToken* token) {
}

void Upgrader::downgrade(BoardToken* token) {
}

bool Upgrader::isAffectingEnemies() {
  return affectsEnemies;
}

void Upgrader::addBoardToken(BoardToken* token) {
  module -> addBoardToken(token);
  upgrade(token);
}

void Upgrader::removeBoardToken(BoardToken* token) {
  module -> removeBoardToken(token);
  downgrade(token);
}
