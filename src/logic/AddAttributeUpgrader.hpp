#ifndef ADDATTRIBUTEUPGRADER_HPP
#define ADDATTRIBUTEUPGRADER_HPP

#include "Upgrader.hpp"

class AddAttributeUpgrader : public Upgrader
{
public:
  AddAttributeUpgrader(Module* module, AttributeName attributeId, std::string name, bool affectsEnemies = false);
  ~AddAttributeUpgrader() {}

protected:
  void upgrade(BoardToken *token);
  void downgrade(BoardToken *token);

private:
  AttributeName newAttributeId;
  std::string newAttributeName;

};

#endif //ADDATTRIBUTEUPGRADER_HPP
