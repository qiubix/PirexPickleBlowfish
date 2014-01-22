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

private:
  //REVIEW: TODO: why this? base class Module has army field, why just don't use it here?
  Army newArmyValue;
};

#endif //CHANGEARMYUPGRADER_HPP
