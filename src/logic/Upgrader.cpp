#include "Upgrader.hpp"

Upgrader::Upgrader(Module* module)
  : Module(module->getArmy(), module->getName(), module->getAttributes())
{
  this->module = module;
}

void Upgrader::upgrade(BoardToken* token)
{
}


void Upgrader::downgrade(BoardToken* token)
{
}


void Upgrader::addBoardToken(BoardToken* token)
{
  module->addBoardToken(token);
  upgrade(token);
}


void Upgrader::removeBoardToken(BoardToken* token)
{
  module->removeBoardToken(token);
  downgrade(token);
}

