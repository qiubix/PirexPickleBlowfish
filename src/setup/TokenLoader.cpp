#include "TokenLoader.hpp"

#include <cstdlib> //NULL

#include "JsonParser.hpp"

TokenLoader * TokenLoader::instance = NULL;

TokenLoader * TokenLoader::getInstance()
{
  if(instance == NULL) {
    instance = new TokenLoader();
  }
  return instance;
}

TokenLoader::TokenLoader() {
}

void TokenLoader::loadArmies(std::vector<std::string> armyJsonFiles) {
  for(int currentArmyFile = 0; currentArmyFile < armyJsonFiles.size(); currentArmyFile++) {
    loadArmy(armyJsonFiles[currentArmyFile]);
  }
}

void TokenLoader::loadArmy(std::string armyFile) {
  Json* armyJson = JsonParser::getInstance() -> parse(armyFile);
  Army army = StringToEnumTranslator::getInstance() -> getArmy(armyJson -> getStringValue("army"));

  loadHeadquarters(army, armyJson -> getObject("headquarters"));
  loadInstantTokens(army, armyJson -> getArray("instants"));
  loadModuleTokens(army, armyJson -> getArray("modules"));
  loadUnitTokens(army, armyJson -> getArray("units"));
  delete armyJson;
}

void TokenLoader::loadHeadquarters(Army army, Json headquarters) {
  //TODO: implement
}

void TokenLoader::loadInstantTokens(Army army, std::vector<Json> instantTokens) {
  for(int currentInstantToken = 0; currentInstantToken < instantTokens.size(); currentInstantToken++) {
    loadInstantToken(army, instantTokens[currentInstantToken]);
  }
}

void TokenLoader::loadInstantToken(Army army, Json instantToken) {
  std::string name = instantToken.getStringValue("name");
  int count = instantToken.getIntegerValue("count");
  //TODO: implement
}

void TokenLoader::loadModuleTokens(Army army, std::vector<Json> moduleTokens) {
  for(int currentModuleToken = 0; currentModuleToken < moduleTokens.size(); currentModuleToken++) {
    loadModuleToken(army, moduleTokens[currentModuleToken]);
  }
}

void TokenLoader::loadModuleToken(Army army, Json moduleToken) {
  std::string name = moduleToken.getStringValue("name");
  int count = moduleToken.getIntegerValue("count");
  Attributes* attributes = loadModuleAtrributes(moduleToken.getArray("attributes"));
  std::vector<Side> activeEdges = loadModuleActiveEdges(moduleToken.getStringArray("sides")); //TODO: change to edges (in all json files)
//  ModuleToken* module = new ModuleToken(army, name, attributes, activeEdges);



  //TODO: implement
}

Attributes* TokenLoader::loadModuleAtrributes(std::vector<Json> attributes) {
  Attributes* moduleAttributes = new Attributes();
  Attribute* attributeToAdd;
  for(int currentAttribute = 0; currentAttribute < attributes.size(); currentAttribute++) {
    attributeToAdd = loadModuleAttribute(attributes[currentAttribute]);
    AttributeName attributeName = StringToEnumTranslator::getInstance() -> getAttributeName(attributeToAdd -> getName());
    moduleAttributes -> addAttribute(attributeName, attributeToAdd);
  }
  return moduleAttributes;
}

//TODO: add validation (name must exist)
Attribute* TokenLoader::loadModuleAttribute(Json attribute) {
  Attribute* moduleAttribute = NULL;
  std::string name = attribute.getStringValue("name");
  int value = attribute.getIntegerValue("value");
  moduleAttribute = new Attribute(name, value);
  return moduleAttribute;
}

std::vector<Side> TokenLoader::loadModuleActiveEdges(std::vector<std::string> edges) {
  std::vector<Side> activeEdges;
  for(int currentEdge = 0; currentEdge < edges.size(); currentEdge++) {
    activeEdges.push_back(StringToEnumTranslator::getInstance() -> getSide(edges[currentEdge]));
  }
  return activeEdges;
}

void TokenLoader::loadUnitTokens(Army army, std::vector<Json> unitTokens) {
  for(int currentUnitToken = 0; currentUnitToken < unitTokens.size(); currentUnitToken++) {
    loadUnitToken(army, unitTokens[currentUnitToken]);
  }
}

void TokenLoader::loadUnitToken(Army army, Json unitToken) {
  std::string name = unitToken.getStringValue("name");
  int count = unitToken.getIntegerValue("count");
  //TODO: implement
}
