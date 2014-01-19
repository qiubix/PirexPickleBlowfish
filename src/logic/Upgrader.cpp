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


void Upgrader::addBoardToken(BoardToken* token, Side edge)
{
  module->addBoardToken(token, edge);
  upgrade(token);
}


void Upgrader::removeBoardToken(BoardToken* token, Side edge)
{
  module->removeBoardToken(token, edge);
  downgrade(token);
}

