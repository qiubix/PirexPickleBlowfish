#include "TokenLoader.hpp"

#include "JsonParser.hpp"

#include "logic/ChangeArmyUpgrader.hpp"
#include "logic/ChangeAttributeUpgrader.hpp"
#include "logic/AddAttributeUpgrader.hpp"

#include "GameBox.hpp"

TokenLoader * TokenLoader::instance = nullptr;

TokenLoader * TokenLoader::getInstance()
{
  if(instance == nullptr) {
    instance = new TokenLoader();
  }
  return instance;
}

TokenLoader::TokenLoader() {
}

void TokenLoader::loadArmies(std::vector<std::string> armyJsonFiles, Controller* controller) {
  for(int currentArmyFile = 0; currentArmyFile < armyJsonFiles.size(); currentArmyFile++) {
    loadArmy(armyJsonFiles[currentArmyFile], controller);
  }
}

void TokenLoader::loadArmy(std::string armyFile, Controller* controller) {
  Json* armyJson = JsonParser::getInstance() -> parse(armyFile);
  Army army = StringToEnumTranslator::getInstance() -> getArmy(armyJson -> getStringValue("army"));

  GameBox::getInstance() -> addEmptyArmy(army);
//  loadHeadquarters(army, armyJson -> getObject("headquarters"));
  loadInstantTokens(army, armyJson -> getArray("instants"), controller);
  loadModuleTokens(army, armyJson -> getArray("modules"));
  loadUnitTokens(army, armyJson -> getArray("units"));
  delete armyJson;
}

void TokenLoader::loadHeadquarters(Army army, Json headquartersParameters) {
  Json upgradeParameters = headquartersParameters.getObject("upgrade");
  Module * headquarters = createHeadquarters(army, upgradeParameters);
  GameBox::getInstance() -> addTokenToArmy(army, headquarters);
}

Module* TokenLoader::createHeadquarters(Army army, Json& upgradeParameters) {
  HeadquartersToken* headquarters = new HeadquartersToken(army, "Headquarters", nullptr);
  std::vector<std::string> upgrades = upgradeParameters.getKeys();
  AttributeName attributeName = StringToEnumTranslator::getInstance() -> getAttributeName(upgrades[0]);
  int value = upgradeParameters.getIntegerValue(upgrades[0]);
  if (attributeName < SHIELD) {
    return new ChangeAttributeUpgrader(headquarters, attributeName, value);
  } else {
    return new AddAttributeUpgrader(headquarters, attributeName, upgrades[0]);
  }
}

void TokenLoader::loadInstantTokens(Army army, std::vector<Json> instantTokens, Controller* controller) {
  for(int currentInstantToken = 0; currentInstantToken < instantTokens.size(); currentInstantToken++) {
    loadInstantToken(army, instantTokens[currentInstantToken], controller);
  }
}

void TokenLoader::loadInstantToken(Army army, Json instantTokenParameters, Controller* controller) {
  std::string name = instantTokenParameters.getStringValue("name");
  int count = instantTokenParameters.getIntegerValue("count");

  for(int currentInstantToken = 0; currentInstantToken < count; currentInstantToken++) {
    InstantToken* token = createInstantToken(army, name, controller);
    GameBox::getInstance() -> addTokenToArmy(army, token);
  }
}

//FIXME: do something with adding real controller
InstantToken* TokenLoader::createInstantToken(Army army, std::string name, Controller* controller) {
  if(name.compare("Battle") == 0) {
    return new BattleToken(army, controller);
  }
  if(name.compare("Move") == 0) {
    return new MovementToken(army, controller);
  }
  if(name.compare("Push back") == 0) {
    return new PushToken(army, controller);
  }
  if(name.compare("Air strike") == 0) {
    return new BombToken(army, controller);
  }
  if(name.compare("Grenade") == 0) {
    return new GrenadeToken(army, controller);
  }
  if(name.compare("Sniper") == 0) {
    return new SniperToken(army, controller);
  }
}

void TokenLoader::loadModuleTokens(Army army, std::vector<Json> moduleTokens) {
  for(int currentModuleToken = 0; currentModuleToken < moduleTokens.size(); currentModuleToken++) {
    loadModuleToken(army, moduleTokens[currentModuleToken]);
  }
}

//TODO: TESTME: test adding ModuleToken process
void TokenLoader::loadModuleToken(Army army, Json moduleTokenParameters) {
  std::string name = moduleTokenParameters.getStringValue("name");
  int count = moduleTokenParameters.getIntegerValue("count"); //FIXME: use count!
  Attributes* attributes = loadModuleAtrributes(moduleTokenParameters.getArray("attributes"));
  std::vector<Side> activeEdges = loadModuleActiveEdges(moduleTokenParameters.getStringArray("sides")); //TODO: change to edges (in all json files)

  for(int currentModule = 0; currentModule < count; currentModule++) {
    ModuleToken* moduleToken = new ModuleToken(army, name, attributes, activeEdges);
    Module* module = decorateModuleWithUpgrades(moduleToken, moduleTokenParameters.getArray("upgrades"));
    GameBox::getInstance() -> addTokenToArmy(army, module);
  }
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
  Attribute* moduleAttribute = nullptr;
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

Module* TokenLoader::decorateModuleWithUpgrades(ModuleToken* moduleToken, std::vector<Json> upgradesParameters) {
  Module* module = moduleToken;
  for(int currentUpgrade = 0; currentUpgrade < upgradesParameters.size(); currentUpgrade++) {
    Json currentUpgradeParameters = upgradesParameters[currentUpgrade];
    std::string name = currentUpgradeParameters.getStringValue("name");
    AttributeName attributeName = StringToEnumTranslator::getInstance() -> getAttributeName(name);
    int value = currentUpgradeParameters.getIntegerValue("value");
    bool affectsEnemy = currentUpgradeParameters.getBooleanValue("affectsEnemy");

    if(attributeName == ARMY) {
      module = new ChangeArmyUpgrader(module, affectsEnemy);
    } else if (attributeName < SHIELD) {
      module = new ChangeAttributeUpgrader(module, attributeName, value, affectsEnemy);
    } else {
      module = new AddAttributeUpgrader(module, attributeName, name, affectsEnemy);
    }
  }
  return module;
}

void TokenLoader::loadUnitTokens(Army army, std::vector<Json> unitTokens) {
  for(int currentUnitToken = 0; currentUnitToken < unitTokens.size(); currentUnitToken++) {
    loadUnitToken(army, unitTokens[currentUnitToken]);
  }
}

//TODO: TESTME: test adding UnitToken process
void TokenLoader::loadUnitToken(Army army, Json unitTokenParameters) {
  std::string name = unitTokenParameters.getStringValue("name");
  int count = unitTokenParameters.getIntegerValue("count");

  for(int currentUnit = 0; currentUnit < count; currentUnit++) {
    Attributes* attributes = loadUnitAttributes(unitTokenParameters);
    UnitToken* token = new UnitToken(army, name, attributes);
    loadUnitSideAttributes(token, unitTokenParameters);
    GameBox::getInstance() -> addTokenToArmy(army, token);
  }
}

//TODO: TESTME: some test to check if format of data in json is correct
Attributes* TokenLoader::loadUnitAttributes(Json unitTokenParameters) {
  Attributes* attributes = new Attributes();
  loadInitiative(unitTokenParameters.getIntegerArray("initiative"), attributes);
  loadMove(unitTokenParameters.getBooleanValue("move"), attributes); //TODO: change move in all .json to mobility
  loadToughness(unitTokenParameters.getIntegerValue("toughness"), attributes);
  return attributes;
}

void TokenLoader::loadInitiative(std::vector<int> initiativeParameters, Attributes* attributes) {
  AttributeName initiative = StringToEnumTranslator::getInstance() -> getAttributeName("initiative");
  for(int currentInitiativeParameter = 0; currentInitiativeParameter < initiativeParameters.size(); currentInitiativeParameter++) {
    attributes -> addAttribute(initiative, new Attribute("initiative", initiativeParameters[currentInitiativeParameter]));
  }
}

void TokenLoader::loadMove(bool haveMoveAbility, Attributes* attributes) {
  if(haveMoveAbility) {
    AttributeName mobility = StringToEnumTranslator::getInstance() -> getAttributeName("mobility");
    attributes -> addAttribute(mobility, new Attribute("mobility", 1));
  }
}

void TokenLoader::loadToughness(int additionalToughness, Attributes* attributes) {
  AttributeName toughness = StringToEnumTranslator::getInstance() -> getAttributeName("toughness");
  attributes -> addAttribute(toughness, new Attribute("toughness", 1 + additionalToughness));
}

void TokenLoader::loadUnitSideAttributes(UnitToken* token, Json unitTokenParameters) {
  Json meleeParameters = unitTokenParameters.getObject("melee"); //TEST na default
  Json rangedParameters = unitTokenParameters.getObject("ranged");
  loadMelee(token, meleeParameters);
  loadRanged(token, rangedParameters);
  loadShield(token, unitTokenParameters.getStringArray("armor"));
  loadNet(token, unitTokenParameters.getStringArray("net"));
}

//FIXME: REFACTOR: duplication in two methods below
void TokenLoader::loadMelee(UnitToken* token, Json& meleeParameters) {
  std::vector<std::string> sides = meleeParameters.getKeys();
  AttributeName attributeName = StringToEnumTranslator::getInstance() -> getAttributeName("melee");
  for(int currentSide = 0; currentSide < sides.size(); currentSide++) {
    Side side = StringToEnumTranslator::getInstance() -> getSide(sides[currentSide]);
    int value = meleeParameters.getIntegerValue(sides[currentSide]);
    token -> getEdgeAttributes(side) -> addAttribute(attributeName, new Attribute("melee", value));
  }
}

void TokenLoader::loadRanged(UnitToken* token, Json& rangedParameters) {
  std::vector<std::string> sides = rangedParameters.getKeys();
  AttributeName attributeName = StringToEnumTranslator::getInstance() -> getAttributeName("ranged");
  for(int currentSide = 0; currentSide < sides.size(); currentSide++) {
    Side side = StringToEnumTranslator::getInstance() -> getSide(sides[currentSide]);
    int value = rangedParameters.getIntegerValue(sides[currentSide]);
    token -> getEdgeAttributes(side) -> addAttribute(attributeName, new Attribute("ranged", value));
  }
}

//FIXME: REFACTOR: duplication in two methods below
void TokenLoader::loadShield(UnitToken* token, std::vector<std::string> shieldParameters) {
  AttributeName shield = StringToEnumTranslator::getInstance() -> getAttributeName("shield");
  for(int currentShieldParameter = 0; currentShieldParameter < shieldParameters.size(); currentShieldParameter++) {
    Side side = StringToEnumTranslator::getInstance() -> getSide(shieldParameters[currentShieldParameter]);
    token -> getEdgeAttributes(side) -> addAttribute(shield, new Attribute("shield", 1));
  }
}

void TokenLoader::loadNet(UnitToken* token, std::vector<std::string> netParameters) {
  AttributeName net = StringToEnumTranslator::getInstance() -> getAttributeName("net");
  for(int currentNetParameter = 0; currentNetParameter < netParameters.size(); currentNetParameter++) {
    Side side = StringToEnumTranslator::getInstance() -> getSide(netParameters[currentNetParameter]);
    token -> getEdgeAttributes(side) -> addAttribute(net, new Attribute("net", 1));
  }
}
