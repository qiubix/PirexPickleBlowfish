#include <gmock/gmock.h>
using ::testing::Eq;
using ::testing::Return;
#include <gtest/gtest.h>
using ::testing::Test;
using ::testing::_;

#include "setup/TokenLoader.hpp"
#include "MockJson.hpp"

#include "setup/JsonParser.hpp"

#include "logic/ChangeAttributeUpgrader.hpp"
#include "logic/AddAttributeUpgrader.hpp"

#include <fstream>

//TODO: write separate test fixture for modules, units, instants and hqs
//TODO: add more mocks but first make it possible in Json class (method to add fields in json needed to nicely mock)
class TokenLoaderTest : public Test {
protected:
  TokenLoaderTest() {}

  virtual ~TokenLoaderTest() {}

  virtual void SetUp() {}
  virtual void TearDown() {}

  void createShortJsonFile(std::string fileName, std::string content);
  ModuleToken* createModuleToken(Army army = HEGEMONY);
  UnitToken* createUnitToken(Army army = HEGEMONY);
};

void TokenLoaderTest::createShortJsonFile(std::string fileName, std::string content) {
  std::ofstream jsonFile(fileName.c_str());
  if (jsonFile.is_open()) {
    jsonFile << content;
    jsonFile.close();
  }
}

ModuleToken* TokenLoaderTest::createModuleToken(Army army) {
  std::vector<Side> activeEdges;
  return new ModuleToken(army, "Boss", new Attributes(), activeEdges);
}

UnitToken* TokenLoaderTest::createUnitToken(Army army) {
  Attributes* northSideAttributes = new Attributes();
  northSideAttributes -> addAttribute(MELEE, new Attribute("melee", 1));
  northSideAttributes -> addAttribute(RANGED, new Attribute("ranged", 1));

  Attributes* baseAttributes = new Attributes();
  baseAttributes -> addAttribute(INITIATIVE, new Attribute("initiative", 1));

  UnitToken* unit = new UnitToken(army, "someUnit", baseAttributes);
  unit->setEdgeAttributes(Side::NORTH, northSideAttributes);
  return unit;
}

TEST_F(TokenLoaderTest, shouldLoadTheTestFile) {
  Json* json = JsonParser::getInstance() -> parse("test.json");
  ASSERT_FALSE(json->isEmpty());
}

TEST_F(TokenLoaderTest, shouldLoadModuleAttributes) {
  const std::string ATTRIBUTE = "toughness";
  createShortJsonFile("moduleWithAttribute.json", "{\"attributes\": [{\"name\": \"" + ATTRIBUTE + "\", \"value\":1}]}");
  Json* moduleWithAttribute = JsonParser::getInstance() -> parse("moduleWithAttribute.json");
  Attributes* moduleWithAttributeAttributes = TokenLoader::getInstance() -> loadModuleAtrributes(moduleWithAttribute->getArray("attributes"));
  ASSERT_NE((Attributes*)nullptr, moduleWithAttributeAttributes);
  ASSERT_FALSE(moduleWithAttributeAttributes -> empty());
  AttributeName attributeName = StringToEnumTranslator::getInstance() -> getAttributeName(ATTRIBUTE);
  Attribute* moduleAttribute = moduleWithAttributeAttributes -> getAttribute(attributeName);
  ASSERT_EQ(1, moduleAttribute -> getValue());

  createShortJsonFile("moduleWithNoAttribute.json", "{}");
  Json* moduleWithNoAttribute = JsonParser::getInstance() -> parse("moduleWithNoAttribute.json");
  Attributes* moduleWithNoAttributeAttributes = TokenLoader::getInstance() -> loadModuleAtrributes(moduleWithNoAttribute->getArray("attributes"));
  ASSERT_NE((Attributes*)nullptr, moduleWithNoAttributeAttributes);
  ASSERT_TRUE(moduleWithNoAttributeAttributes -> empty());
}

//TODO: mock instead of file
TEST_F(TokenLoaderTest, shouldLoadModuleActiveEdges) {
  createShortJsonFile("someActiveEdges.json", "{\"sides\": [\"north\", \"south\"]}");
  Json* someActiveEdges = JsonParser::getInstance() -> parse("someActiveEdges.json");
  std::vector<Side> expectedActiveEdges;
  expectedActiveEdges.push_back(Side::NORTH);
  expectedActiveEdges.push_back(Side::SOUTH);
  std::vector<Side> activeEdges = TokenLoader::getInstance() -> loadModuleActiveEdges(someActiveEdges->getStringArray("sides"));
  ASSERT_EQ(expectedActiveEdges.size(), activeEdges.size());
  for(int currentActiveEdge = 0; currentActiveEdge < expectedActiveEdges.size(); currentActiveEdge++) {
    ASSERT_EQ(expectedActiveEdges[currentActiveEdge], activeEdges[currentActiveEdge]);
  }
}

//FIXME: delete dynamically allocated objects - but first check destructors of Module, ModuleToken, Upgrader and its children
//FIXME: below tests should test creating the module not its behaviour
TEST_F(TokenLoaderTest, shouldDecorateModuleWithTwoChangeAttributeUpgrades) {
  Json* upgradesParameters = JsonParser::getInstance() -> parse("twoChangeAttributeUpgradesParameters.json");
  ASSERT_FALSE(upgradesParameters -> isEmpty());

  ModuleToken* moduleToken = createModuleToken();
  Module* module = TokenLoader::getInstance() -> decorateModuleWithUpgrades(moduleToken, upgradesParameters->getArray("upgrades"));
  ASSERT_TRUE(dynamic_cast<Upgrader *>(module));
  ASSERT_FALSE(dynamic_cast<Upgrader *>(module) -> isAffectingEnemies());

  UnitToken* unit = createUnitToken();
  ASSERT_EQ(1, unit -> getAttribute(INITIATIVE) -> getValue());
  ASSERT_EQ(1, unit -> getEdgeAttributes(Side::NORTH) -> getAttribute(MELEE) -> getValue());
  ASSERT_EQ(1, unit -> getEdgeAttributes(Side::NORTH) -> getAttribute(RANGED) -> getValue());

  module -> addBoardToken(unit);
  ASSERT_EQ(3, unit -> getAttribute(INITIATIVE) -> getValue());
  ASSERT_EQ(2, unit -> getEdgeAttributes(Side::NORTH) -> getAttribute(MELEE) -> getValue());
  ASSERT_EQ(1, unit -> getEdgeAttributes(Side::NORTH) -> getAttribute(RANGED) -> getValue());
}

TEST_F(TokenLoaderTest, shouldDecorateModuleWithOneChangeAttributeOfEnemyUpgrade) {
  Json* upgradesParameters = JsonParser::getInstance() -> parse("oneChangeAttributeOfEnemyUpgradeParameters.json");
  ASSERT_FALSE(upgradesParameters -> isEmpty());

  ModuleToken* moduleToken = createModuleToken();
  Module* module = TokenLoader::getInstance() -> decorateModuleWithUpgrades(moduleToken, upgradesParameters->getArray("upgrades"));
  ASSERT_TRUE(dynamic_cast<Upgrader *>(module));
  ASSERT_TRUE(dynamic_cast<Upgrader *>(module) -> isAffectingEnemies());

  UnitToken* unit = createUnitToken(OUTPOST);
  ASSERT_EQ(1, unit -> getAttribute(INITIATIVE) -> getValue());
  ASSERT_EQ(1, unit -> getEdgeAttributes(Side::NORTH) -> getAttribute(MELEE) -> getValue());
  ASSERT_EQ(1, unit -> getEdgeAttributes(Side::NORTH) -> getAttribute(RANGED) -> getValue());

  module -> addBoardToken(unit);
  ASSERT_EQ(0, unit -> getAttribute(INITIATIVE) -> getValue());
  ASSERT_EQ(1, unit -> getEdgeAttributes(Side::NORTH) -> getAttribute(MELEE) -> getValue());
  ASSERT_EQ(1, unit -> getEdgeAttributes(Side::NORTH) -> getAttribute(RANGED) -> getValue());
}

TEST_F(TokenLoaderTest, shouldDecorateModuleWithChangeArmyUpgrade) {
  Json* upgradesParameters = JsonParser::getInstance() -> parse("changeArmyUpgradeParameters.json");
  ASSERT_FALSE(upgradesParameters -> isEmpty());

  ModuleToken* moduleToken = createModuleToken();
  Module* module = TokenLoader::getInstance() -> decorateModuleWithUpgrades(moduleToken, upgradesParameters->getArray("upgrades"));
  ASSERT_TRUE(dynamic_cast<Upgrader *>(module));
  ASSERT_TRUE(dynamic_cast<Upgrader *>(module) -> isAffectingEnemies());

  UnitToken* unit = createUnitToken(OUTPOST);
  ASSERT_EQ(OUTPOST, unit -> getArmy());

  module -> addBoardToken(unit);
  ASSERT_EQ(HEGEMONY, unit -> getArmy());
}

TEST_F(TokenLoaderTest, shouldDecorateModuleWithTwoAddAttributeUpgrades) {
  Json* upgradesParameters = JsonParser::getInstance() -> parse("twoAddAttributeUpgradesParameters.json");
  ASSERT_FALSE(upgradesParameters -> isEmpty());

  ModuleToken* moduleToken = createModuleToken();
  Module* module = TokenLoader::getInstance() -> decorateModuleWithUpgrades(moduleToken, upgradesParameters->getArray("upgrades"));
  ASSERT_TRUE(dynamic_cast<Upgrader *>(module));
  ASSERT_FALSE(dynamic_cast<Upgrader *>(module) -> isAffectingEnemies());

  UnitToken* unit = createUnitToken();
  ASSERT_EQ((Attribute *)nullptr, unit -> getAttribute(MOTHER));
  ASSERT_EQ((Attribute *)nullptr, unit -> getAttribute(QUARTERMASTER));

  module -> addBoardToken(unit);
  ASSERT_NE((Attribute *)nullptr, unit -> getAttribute(MOTHER));
  ASSERT_NE((Attribute *)nullptr, unit -> getAttribute(QUARTERMASTER));
}

TEST_F(TokenLoaderTest, shouldDecorateModuleWithOneAddAttributeAndOneChangeAttributeUpgrades) {
  Json* upgradesParameters = JsonParser::getInstance() -> parse("oneAddAttributeAndOneChangeAttributeUpgradesParameters.json");
  ASSERT_FALSE(upgradesParameters -> isEmpty());

  ModuleToken* moduleToken = createModuleToken();
  Module* module = TokenLoader::getInstance() -> decorateModuleWithUpgrades(moduleToken, upgradesParameters->getArray("upgrades"));
  ASSERT_TRUE(dynamic_cast<Upgrader *>(module));
  ASSERT_FALSE(dynamic_cast<Upgrader *>(module) -> isAffectingEnemies());

  UnitToken* unit = createUnitToken();
  ASSERT_EQ(1, unit -> getAttribute(INITIATIVE) -> getValue());
  ASSERT_EQ((Attribute *)nullptr, unit -> getAttribute(MOTHER));

  module -> addBoardToken(unit);
  ASSERT_EQ(2, unit -> getAttribute(INITIATIVE) -> getValue());
  ASSERT_NE((Attribute *)nullptr, unit -> getAttribute(MOTHER));
}

//TODO: maybe split this test into three tests
//FIXME: add test and funcinallity for multiinitiative
TEST_F(TokenLoaderTest, shouldAddInitiativeLoadedFromJsonToAttributes) {
  std::vector<int> initiativeParameters;
  Attributes* attributes = new Attributes();

  TokenLoader::getInstance() -> loadInitiative(initiativeParameters, attributes);
  ASSERT_TRUE(attributes -> empty());

  initiativeParameters.push_back(1);
  TokenLoader::getInstance() -> loadInitiative(initiativeParameters, attributes);
  ASSERT_EQ(1, attributes -> getSize());
  ASSERT_EQ("initiative", attributes -> getAttribute(INITIATIVE) -> getName());
  ASSERT_EQ(1, attributes -> getAttribute(INITIATIVE) -> getValue());
}

//TODO: again, maybe two separate tests?
TEST_F(TokenLoaderTest, shouldAddMobilityFromJsonToAttributes) {
  Attributes* attributes = new Attributes();

  TokenLoader::getInstance() -> loadMove(false, attributes);
  ASSERT_TRUE(attributes -> empty());

  TokenLoader::getInstance() -> loadMove(true, attributes);
  ASSERT_EQ(1, attributes -> getSize());
  ASSERT_EQ("mobility", attributes -> getAttribute(MOBILITY) -> getName());
  ASSERT_EQ(1, attributes -> getAttribute(MOBILITY) -> getValue());
}

TEST_F(TokenLoaderTest, shouldAddToughnessFromJsonToAttributes) {
  Attributes* attributes = new Attributes();

  TokenLoader::getInstance() -> loadToughness(0, attributes);
  ASSERT_EQ(1, attributes -> getSize());
  ASSERT_EQ("toughness", attributes -> getAttribute(TOUGHNESS) -> getName());
  ASSERT_EQ(1, attributes -> getAttribute(TOUGHNESS) -> getValue());

  attributes -> removeAttribute(TOUGHNESS);
  ASSERT_TRUE(attributes -> empty());

  TokenLoader::getInstance() -> loadToughness(2, attributes);
  ASSERT_EQ(1, attributes -> getSize());
  ASSERT_EQ("toughness", attributes -> getAttribute(TOUGHNESS) -> getName());
  ASSERT_EQ(3, attributes -> getAttribute(TOUGHNESS) -> getValue());
}

//FIXME: REFACTOR: duplication in two tests below
TEST_F(TokenLoaderTest, shouldAddMeleeAttributesToToken) {
  MockJson json;
  std::vector<std::string> keys;
  keys.push_back("north");
  keys.push_back("south");
  keys.push_back("northWest");
  const int NORTH_VALUE = 1;
  const int SOUTH_VALUE = 2;
  const int NORTH_WEST_VALUE = 1;
  ON_CALL(json, getKeys())
    .WillByDefault(Return(keys));
  ON_CALL(json, getIntegerValue(keys[0]))
    .WillByDefault(Return(NORTH_VALUE));
  ON_CALL(json, getIntegerValue(keys[1]))
    .WillByDefault(Return(SOUTH_VALUE));
  ON_CALL(json, getIntegerValue(keys[2]))
    .WillByDefault(Return(NORTH_WEST_VALUE));
  EXPECT_CALL(json, getKeys())
    .Times(1);
  EXPECT_CALL(json, getIntegerValue(_))
    .Times(keys.size());

  Army army = HEGEMONY;
  std::string name = "someName";
  Attributes* attributes = new Attributes();
  UnitToken* token = new UnitToken(army, name, attributes);
  TokenLoader::getInstance() -> loadMelee(token, json);

  ASSERT_EQ(NORTH_VALUE, token -> getEdgeAttributes(Side::NORTH) -> getAttribute(MELEE) -> getValue());
  ASSERT_EQ(SOUTH_VALUE, token -> getEdgeAttributes(Side::SOUTH) -> getAttribute(MELEE) -> getValue());
  ASSERT_EQ(NORTH_WEST_VALUE, token -> getEdgeAttributes(Side::NORTH_WEST) -> getAttribute(MELEE) -> getValue());
}

TEST_F(TokenLoaderTest, shouldAddRangedAttributesToToken) {
  MockJson json;
  std::vector<std::string> keys;
  keys.push_back("north");
  keys.push_back("south");
  keys.push_back("northWest");
  const int NORTH_VALUE = 1;
  const int SOUTH_VALUE = 2;
  const int NORTH_WEST_VALUE = 1;
  ON_CALL(json, getKeys())
    .WillByDefault(Return(keys));
  ON_CALL(json, getIntegerValue(keys[0]))
    .WillByDefault(Return(NORTH_VALUE));
  ON_CALL(json, getIntegerValue(keys[1]))
    .WillByDefault(Return(SOUTH_VALUE));
  ON_CALL(json, getIntegerValue(keys[2]))
    .WillByDefault(Return(NORTH_WEST_VALUE));
  EXPECT_CALL(json, getKeys())
    .Times(1);
  EXPECT_CALL(json, getIntegerValue(_))
    .Times(keys.size());

  Army army = HEGEMONY;
  std::string name = "someName";
  Attributes* attributes = new Attributes();
  UnitToken* token = new UnitToken(army, name, attributes);
  TokenLoader::getInstance() -> loadRanged(token, json);

  ASSERT_EQ(NORTH_VALUE, token -> getEdgeAttributes(Side::NORTH) -> getAttribute(RANGED) -> getValue());
  ASSERT_EQ(SOUTH_VALUE, token -> getEdgeAttributes(Side::SOUTH) -> getAttribute(RANGED) -> getValue());
  ASSERT_EQ(NORTH_WEST_VALUE, token -> getEdgeAttributes(Side::NORTH_WEST) -> getAttribute(RANGED) -> getValue());
}

//FIXME: REFACTOR: duplication in two tests below
TEST_F(TokenLoaderTest, shouldAddShieldAttributesToToken) {
  std::vector<std::string> shieldParameters; //TODO: TESTME: empty vector by default in json.getStringArray
  shieldParameters.push_back("north");
  shieldParameters.push_back("northEast");

  Army army = HEGEMONY;
  std::string name = "someName";
  Attributes* attributes = new Attributes();
  UnitToken* token = new UnitToken(army, name, attributes);

  TokenLoader::getInstance() -> loadShield(token, shieldParameters);

  Attribute * northSideShieldAttribute = token -> getEdgeAttributes(Side::NORTH) -> getAttribute(SHIELD);
  ASSERT_NE((Attribute*)nullptr, northSideShieldAttribute);
  ASSERT_EQ("shield", northSideShieldAttribute -> getName());
  ASSERT_EQ(1, northSideShieldAttribute -> getValue());

  Attribute * northEastSideShieldAttribute = token -> getEdgeAttributes(Side::NORTH_EAST) -> getAttribute(SHIELD);
  ASSERT_NE((Attribute*)nullptr, northEastSideShieldAttribute);
  ASSERT_EQ("shield", northEastSideShieldAttribute -> getName());
  ASSERT_EQ(1, northEastSideShieldAttribute -> getValue());
}

TEST_F(TokenLoaderTest, shouldAddNetAttributesToToken) {
  std::vector<std::string> netParameters; //TODO: TESTME: empty vector by default in json.getStringArray
  netParameters.push_back("north");
  netParameters.push_back("northEast");

  Army army = HEGEMONY;
  std::string name = "someName";
  Attributes* attributes = new Attributes();
  UnitToken* token = new UnitToken(army, name, attributes);

  TokenLoader::getInstance() -> loadNet(token, netParameters);

  Attribute * northSideNetAttribute = token -> getEdgeAttributes(Side::NORTH) -> getAttribute(NET);
  ASSERT_NE((Attribute*)nullptr, northSideNetAttribute);
  ASSERT_EQ("net", northSideNetAttribute -> getName());
  ASSERT_EQ(1, northSideNetAttribute -> getValue());

  Attribute * northEastSideNetAttribute = token -> getEdgeAttributes(Side::NORTH_EAST) -> getAttribute(NET);
  ASSERT_NE((Attribute*)nullptr, northEastSideNetAttribute);
  ASSERT_EQ("net", northEastSideNetAttribute -> getName());
  ASSERT_EQ(1, northEastSideNetAttribute -> getValue());
}

//TODO: figure out how initialize controller in instant tokens without passing it through all loading levels
//TODO: refactor these tests into one maybe
//TODO: when moved to separate test file initialize controller in test suite (if controller would be still needed)
TEST_F(TokenLoaderTest, shouldCreateBattleToken) {
  Controller * controller = new Controller(new Model());
  InstantToken* token = TokenLoader::getInstance() -> createInstantToken(HEGEMONY, "Battle", controller);
  ASSERT_TRUE(dynamic_cast<BattleToken *>(token));
  ASSERT_EQ(controller, token->controller);
  delete controller;
}

TEST_F(TokenLoaderTest, shouldCreateMovementToken) {
  Controller * controller = new Controller(new Model());
  InstantToken* token = TokenLoader::getInstance() -> createInstantToken(HEGEMONY, "Move", controller);
  ASSERT_TRUE(dynamic_cast<MovementToken *>(token));
  ASSERT_EQ(controller, token->controller);
  delete controller;
}

TEST_F(TokenLoaderTest, shouldCreatePushToken) {
  Controller * controller = new Controller(new Model());
  InstantToken* token = TokenLoader::getInstance() -> createInstantToken(HEGEMONY, "Push back", controller);
  ASSERT_TRUE(dynamic_cast<PushToken *>(token));
  ASSERT_EQ(controller, token->controller);
  delete controller;
}

TEST_F(TokenLoaderTest, shouldCreateBombToken) {
  Controller * controller = new Controller(new Model());
  InstantToken* token = TokenLoader::getInstance() -> createInstantToken(HEGEMONY, "Air strike", controller);
  ASSERT_TRUE(dynamic_cast<BombToken *>(token));
  ASSERT_EQ(controller, token->controller);
  delete controller;
}

TEST_F(TokenLoaderTest, shouldCreateGrenadeToken) {
  Controller * controller = new Controller(new Model());
  InstantToken* token = TokenLoader::getInstance() -> createInstantToken(HEGEMONY, "Grenade", controller);
  ASSERT_TRUE(dynamic_cast<GrenadeToken *>(token));
  ASSERT_EQ(controller, token->controller);
  delete controller;
}

TEST_F(TokenLoaderTest, shouldCreateSniperToken) {
  Controller * controller = new Controller(new Model());
  InstantToken* token = TokenLoader::getInstance() -> createInstantToken(HEGEMONY, "Sniper", controller);
  ASSERT_TRUE(dynamic_cast<SniperToken *>(token));
  ASSERT_EQ(controller, token->controller);
  delete controller;
}

//TODO: refactor below two tests
TEST_F(TokenLoaderTest, shouldCreateHeadquartersTokenUpgradingAttribute) {
  MockJson json;
  std::vector<std::string> keys;
  keys.push_back("initiative");
  const int INITIATIVE_UPGRADE_VALUE = 1;
  ON_CALL(json, getKeys())
    .WillByDefault(Return(keys));
  ON_CALL(json, getIntegerValue(keys[0]))
    .WillByDefault(Return(INITIATIVE_UPGRADE_VALUE));
  EXPECT_CALL(json, getKeys())
    .Times(1);
  EXPECT_CALL(json, getIntegerValue(_))
    .Times(keys.size());

  Army army = HEGEMONY;
  Module* headquarters = TokenLoader::getInstance() -> createHeadquarters(army, json);

//  ASSERT_TRUE(dynamic_cast<HeadquartersToken *>(headquarters));
  ASSERT_TRUE(dynamic_cast<ChangeAttributeUpgrader *>(headquarters));
  EXPECT_EQ(INITIATIVE, dynamic_cast<ChangeAttributeUpgrader *>(headquarters) -> attributeToChange);
  EXPECT_EQ(1, dynamic_cast<ChangeAttributeUpgrader *>(headquarters) -> changeValue);
}

TEST_F(TokenLoaderTest, shouldCreateHeadquartersTokenAddingAttribute) {
  MockJson json;
  std::vector<std::string> keys;
  keys.push_back("mother");
  ON_CALL(json, getKeys())
    .WillByDefault(Return(keys));
  EXPECT_CALL(json, getKeys())
    .Times(1);

  Army army = HEGEMONY;
  Module* headquarters = TokenLoader::getInstance() -> createHeadquarters(army, json);

//  ASSERT_TRUE(dynamic_cast<HeadquartersToken *>(headquarters));
  ASSERT_TRUE(dynamic_cast<AddAttributeUpgrader *>(headquarters));
  EXPECT_EQ(MOTHER, dynamic_cast<AddAttributeUpgrader *>(headquarters) -> newAttributeId);
  EXPECT_EQ("mother", dynamic_cast<AddAttributeUpgrader *>(headquarters) -> newAttributeName);
}

