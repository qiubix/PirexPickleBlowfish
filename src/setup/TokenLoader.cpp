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
  Army army = getArmy(armyJson -> getStringValue("army"));
  loadHeadquarters(army, armyJson -> getObject("headquarters"));
  loadInstantTokens(army, armyJson -> getArray("instants"));
  loadModuleTokens(army, armyJson -> getArray("modules"));
  loadUnitTokens(army, armyJson -> getArray("units"));
  delete armyJson;
}

Army TokenLoader::getArmy(std::string armyFromJson) {
  static std::map<std::string, Army> armiesDictionary;
  armiesDictionary.insert(std::make_pair<std::string, Army>("Moloch", MOLOCH));
  armiesDictionary.insert(std::make_pair<std::string, Army>("Borgo", BORGO));
  armiesDictionary.insert(std::make_pair<std::string, Army>("Outpost", OUTPOST));
  armiesDictionary.insert(std::make_pair<std::string, Army>("Hegemony", HEGEMONY));

  return armiesDictionary[armyFromJson];
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
  //TODO: implement
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
