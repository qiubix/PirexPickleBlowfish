#include "Upgrade.hpp"

Upgrade::Upgrade(Module* module)
{
  this->module = module;
}

void Upgrade::upgrade(BoardToken* token)
{
  module->upgrade(token);
}


void Upgrade::downgrade(BoardToken* token)
{
  module->downgrade(token);
}


void Upgrade::addBoardToken(BoardToken* token)
{
  module->addBoardToken(token);
}


void Upgrade::removeBoardToken(BoardToken* token)
{
  module->removeBoardToken(token);
}

