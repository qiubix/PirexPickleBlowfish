#ifndef ADDATTRIBUTEUPGRADER_HPP
#define ADDATTRIBUTEUPGRADER_HPP

#include "Upgrader.hpp"

class AddAttributeUpgrader : public Upgrader
{
public:
  AddAttributeUpgrader(Module* module, AttributeName attributeId, std::string name);
  ~AddAttributeUpgrader() {}

protected:
  void upgrade(BoardToken *token);
  void downgrade(BoardToken *token);

private:
  //TODO: refactoring - change names
  AttributeName newAttributeId;
  std::string newAttributeName;

};

#endif //ADDATTRIBUTEUPGRADER_HPP
