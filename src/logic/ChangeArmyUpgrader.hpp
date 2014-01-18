#ifndef CHANGEARMYUPGRADER_HPP
#define CHANGEARMYUPGRADER_HPP

#include "Upgrader.hpp"

class ChangeArmyUpgrader : public Upgrader
{
public:
  ChangeArmyUpgrader(Module* module);
  ~ChangeArmyUpgrader() {}

protected:
  void upgrade(BoardToken *token);
  void downgrade(BoardToken *token);

private:
  Army newArmyValue;
  Army baseArmyValue;
};

#endif //CHANGEARMYUPGRADER_HPP
