#include "AddAttributeUpgrader.hpp"

AddAttributeUpgrader::AddAttributeUpgrader(Module* module, AttributeName attributeId, std::string name, bool affectsEnemies)
  : Upgrader(module, affectsEnemies), newAttributeId(attributeId), newAttributeName(name) {
}

void AddAttributeUpgrader::upgrade(BoardToken* token) {
  Attribute* newAttribute = new Attribute(newAttributeName, 1);
  token->addAttribute(newAttributeId, newAttribute);
}

void AddAttributeUpgrader::downgrade(BoardToken* token) {
  token->removeAttribute(newAttributeId);
}
