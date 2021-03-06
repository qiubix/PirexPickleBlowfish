#ifndef CHANGEATTRIBUTEUPGRADER_HPP
#define CHANGEATTRIBUTEUPGRADER_HPP

#include "Upgrader.hpp"

class ChangeAttributeUpgrader : public Upgrader
{
public:
  ChangeAttributeUpgrader(Module* module, AttributeName name, int changeValue, bool affectsEnemies = false);
  ~ChangeAttributeUpgrader() {}

protected:
  void upgrade(BoardToken *token);
  void downgrade(BoardToken *token);

private:
  AttributeName attributeToChange;
  int changeValue;

  FRIEND_TEST(TokenLoaderTest, shouldCreateHeadquartersTokenUpgradingAttribute);
};


#endif //CHANGEATTRIBUTEUPGRADER_HPP
