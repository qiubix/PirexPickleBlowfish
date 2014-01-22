#include "AddAttributeUpgrader.hpp"

AddAttributeUpgrader::AddAttributeUpgrader(Module* module, AttributeName attributeId, std::string name)
  : Upgrader(module), newAttributeId(attributeId), newAttributeName(name) {
}

void AddAttributeUpgrader::upgrade(BoardToken* token) {
  Attribute* newAttribute = new Attribute(newAttributeName, 1);
  token->addAttribute(newAttributeId, newAttribute);
}


void AddAttributeUpgrader::downgrade(BoardToken* token) {
  token->removeAttribute(newAttributeId);
}
