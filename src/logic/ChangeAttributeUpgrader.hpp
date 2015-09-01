#ifndef CHANGEATTRIBUTEUPGRADER_HPP
#define CHANGEATTRIBUTEUPGRADER_HPP

#include "Upgrader.hpp"

class ChangeAttributeUpgrader : public Upgrader
{
public:
  ChangeAttributeUpgrader(Module* module, AttributeName name, int changeValue, bool affectsEnemies = false);

  AttributeName getAttributeToChange() const;
  int getChangeValue() const;

protected:
  void upgrade(BoardToken *token);
  void downgrade(BoardToken *token);

private:
  AttributeName attributeToChange;
  int changeValue;
};


#endif //CHANGEATTRIBUTEUPGRADER_HPP
