#ifndef ADDATTRIBUTEUPGRADER_HPP
#define ADDATTRIBUTEUPGRADER_HPP

#include "Upgrader.hpp"

class AddAttributeUpgrader : public Upgrader
{
public:
  AddAttributeUpgrader(Module* module, Attribute* attribute);
  ~AddAttributeUpgrader() {}

protected:
  void upgrade(BoardToken *token);
  void downgrade(BoardToken *token);

private:
  Attribute* newAttribute;

};

#endif //ADDATTRIBUTEUPGRADER_HPP
