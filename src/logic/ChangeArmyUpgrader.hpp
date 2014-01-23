#ifndef CHANGEARMYUPGRADER_HPP
#define CHANGEARMYUPGRADER_HPP

#include "Upgrader.hpp"

class ChangeArmyUpgrader : public Upgrader
{
public:
  ChangeArmyUpgrader(Module* module, bool affectsEnemies = false);
  ~ChangeArmyUpgrader() {}

protected:
  void upgrade(BoardToken *token);
  void downgrade(BoardToken *token);
};

#endif //CHANGEARMYUPGRADER_HPP
