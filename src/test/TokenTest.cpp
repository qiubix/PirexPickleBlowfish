#include <gmock/gmock.h>
using ::testing::Eq;
#include <gtest/gtest.h>
using ::testing::Test;

#include <cstdlib>

#include "logic/Attribute.hpp"
#include "logic/BoardToken.hpp"
#include "logic/UnitToken.hpp"
#include "logic/ModuleToken.hpp"
#include "logic/AddAttributeUpgrader.hpp"
#include "logic/ChangeAttributeUpgrader.hpp"
#include "logic/ChangeArmyUpgrader.hpp"
#include "logic/Model.hpp"
#include "logic/Controller.hpp"
#include "logic/InstantToken.hpp"

const int ATTRIBUTE_VALUE = 4;

class AttributeTest : public Test
{
protected:
  AttributeTest() {
    attribute = new Attribute("initiative", ATTRIBUTE_VALUE);
  }
  ~AttributeTest() {
    delete attribute;
  }

  Attribute* attribute;

  virtual void SetUp() {}
  virtual void TearDown() {}
};

TEST_F(AttributeTest, testGetAttributeValues) {
  ASSERT_EQ("initiative", attribute -> getName());
  ASSERT_EQ(ATTRIBUTE_VALUE, attribute -> getValue());
}

TEST_F(AttributeTest, testUpgradeAttribute) {
  attribute -> upgradeBy();
  int upgradedValue = ATTRIBUTE_VALUE + 1;
  ASSERT_EQ(upgradedValue, attribute -> getValue());
  attribute -> upgradeBy(2);
  upgradedValue += 2;
  ASSERT_EQ(upgradedValue, attribute -> getValue());
  attribute -> upgradeTo(ATTRIBUTE_VALUE);
  ASSERT_EQ(ATTRIBUTE_VALUE, attribute -> getValue());
}

TEST_F(AttributeTest, testDowngradeAttribute) {
  attribute -> downgradeBy();
  int downgradedValue = ATTRIBUTE_VALUE - 1;
  ASSERT_EQ(downgradedValue, attribute -> getValue());
  attribute -> downgradeBy(2);
  downgradedValue -= 2;
  ASSERT_EQ(downgradedValue, attribute -> getValue());
  downgradedValue = ATTRIBUTE_VALUE - 1;
  attribute -> downgradeTo(ATTRIBUTE_VALUE-1);
  ASSERT_EQ(downgradedValue, attribute -> getValue());
}

TEST_F(AttributeTest, testResetAttributeValue) {
  attribute -> upgradeTo(ATTRIBUTE_VALUE + 3);
  int value = ATTRIBUTE_VALUE + 3;
  ASSERT_EQ(value, attribute -> getValue());
  attribute -> resetValue();
  value = ATTRIBUTE_VALUE;
  ASSERT_EQ(value, attribute -> getValue());
  attribute -> downgradeTo(ATTRIBUTE_VALUE-1);
  value = ATTRIBUTE_VALUE - 1;
  ASSERT_EQ(value, attribute -> getValue());
  attribute -> resetValue();
  value = ATTRIBUTE_VALUE;
  ASSERT_EQ(value, attribute -> getValue());
}

class AttributesTest : public Test
{
protected:
  AttributesTest() {
  }
  ~AttributesTest() {
  }

  virtual void SetUp() {}
  virtual void TearDown() {}
};

TEST_F(AttributesTest, shouldCreateAttributesObjectWithNoAttributes) {
  Attributes* attributes = new Attributes();
  ASSERT_NE((Attributes *)NULL, attributes);
  ASSERT_TRUE(attributes -> empty());
}

//TODO: test adding and removing attribute

class BoardTokenTest : public Test
{
protected:
  BoardTokenTest() {
    Attributes* attributes = new Attributes;
    initiative = new Attribute("initiative", ATTRIBUTE_VALUE);
    attributes -> addAttribute(INITIATIVE, initiative);
    token = new BoardToken(HEGEMONY, "test board token", attributes);
  }

  ~BoardTokenTest() {
    delete token;
  }

  BoardToken* token;
  Attribute* initiative;

  virtual void SetUp() {}

  virtual void TearDown() {}
};

TEST_F(BoardTokenTest, testGetAttribute) {
  Attribute* attribute = token -> getAttribute(INITIATIVE);
  ASSERT_EQ(initiative, attribute);
  ASSERT_EQ(initiative -> getName(), attribute -> getName());
  ASSERT_EQ(initiative -> getValue(), attribute -> getValue());
}

TEST_F(BoardTokenTest, testModifyAttribute) {
  token -> upgradeAttributeBy(INITIATIVE);
  ASSERT_EQ(ATTRIBUTE_VALUE + 1, token -> getAttribute(INITIATIVE) -> getValue());
  token -> downgradeAttributeBy(INITIATIVE);
  ASSERT_EQ(ATTRIBUTE_VALUE, token -> getAttribute(INITIATIVE) -> getValue());
}

TEST_F(BoardTokenTest, testRemoveAttribute) {
  ASSERT_EQ(1, token -> getAttributes() -> getSize());
  token -> removeAttribute(INITIATIVE);
  ASSERT_EQ(0, token -> getAttributes() -> getSize());
}

TEST_F(BoardTokenTest, testGetOrientation) {
  ASSERT_EQ(NORTH, token -> getOrientation());
}

TEST_F(BoardTokenTest, testSetOrientation) {
  token -> setOrientation(SOUTH);
  ASSERT_EQ(SOUTH, token -> getOrientation());
}

TEST_F(BoardTokenTest, testRotateClockwise) {
  token -> setOrientation(SOUTH);
  token -> rotateClockwise();
  ASSERT_EQ(SOUTH_WEST, token -> getOrientation());
}

TEST_F(BoardTokenTest, testRotateAnticlockwise) {
  token -> setOrientation(SOUTH);
  token -> rotateAnticlockwise();
  ASSERT_EQ(SOUTH_EAST, token -> getOrientation());
}


class UnitTokenTest : public Test
{
protected:
  UnitTokenTest() {
    northSideAttributes = new Attributes;
    Attribute* melee = new Attribute("melee", 1);
    northSideAttributes -> addAttribute(MELEE, melee);
    baseUnitAttributes = new Attributes;
    unit = new UnitToken(HEGEMONY, "UniversalSoldier", baseUnitAttributes);
    unit -> setEdgeAttributes(NORTH, northSideAttributes);
  }
  ~UnitTokenTest() {}
  void SetUp() {}
  void TearDown() {}

  UnitToken* unit;
  Attributes* baseUnitAttributes;
  Attributes* northSideAttributes;
};

TEST_F(UnitTokenTest, testGetSideAttributes) {
  Attributes* attributes = unit -> getEdgeAttributes(NORTH);
  Attribute* melee = northSideAttributes -> getAttribute(MELEE);
  ASSERT_EQ(northSideAttributes, attributes);
  ASSERT_EQ(melee, attributes -> getAttribute(MELEE));
  ASSERT_EQ(melee -> getValue(), attributes -> getAttribute(MELEE) -> getValue());
}


class ModuleTokenTest : public Test
{
protected:
  ModuleTokenTest() {
    initiative = new Attribute("initiative", 2);
    mainUnitAttributes = new Attributes;
    mainUnitAttributes -> addAttribute(INITIATIVE, initiative);
    melee = new Attribute("melee", 1);
    northSideAttributes = new Attributes;
    northSideAttributes  ->  addAttribute(MELEE, melee);
    unit = new UnitToken(HEGEMONY, "UniversalSoldier", mainUnitAttributes);
    unit -> setEdgeAttributes(NORTH, northSideAttributes);
    toughness = new Attribute("toughness", 1);
    mainModuleAttributes = new Attributes;
    mainModuleAttributes -> addAttribute(TOUGHNESS, toughness);
    activeEdges.push_back(NORTH);
    activeEdges.push_back(SOUTH);
  }
  ~ModuleTokenTest() {
    delete unit;
  }
  void SetUp() {}
  void TearDown() {}

  Attribute* initiative;
  Attributes* mainUnitAttributes;
  Attribute* melee;
  Attributes* northSideAttributes;
  UnitToken* unit;
  Attribute* toughness;
  Attributes* mainModuleAttributes;
  std::vector<Side> activeEdges;
};

TEST_F(ModuleTokenTest, shouldNotAffectEnemiesOnDefault) {
  Upgrader* upgrader = new ChangeAttributeUpgrader(new ModuleToken(HEGEMONY, "Officer", mainModuleAttributes, activeEdges), MELEE, 1);
  ASSERT_FALSE(upgrader  ->  isAffectingEnemies());
}

TEST_F(ModuleTokenTest, shouldAffectEnemies) {
  Upgrader* upgrader = new ChangeAttributeUpgrader(new ModuleToken(HEGEMONY, "Officer", mainModuleAttributes, activeEdges), MELEE, 1, true);
  ASSERT_TRUE(upgrader  ->  isAffectingEnemies());
}

TEST_F(ModuleTokenTest, shouldAddBoardToken) {
  ModuleToken* module = new ModuleToken(HEGEMONY, "Officer", mainModuleAttributes, activeEdges);
  EXPECT_TRUE(module -> boardTokens.empty());
  module -> addBoardToken(unit);
  EXPECT_EQ(1, module -> boardTokens.size());
  EXPECT_EQ("UniversalSoldier", module -> boardTokens[0] -> getName());
  delete module;
}

TEST_F(ModuleTokenTest, shouldRemoveBoardToken) {
  ModuleToken* module = new ModuleToken(HEGEMONY, "Officer", mainModuleAttributes, activeEdges);
  UnitToken* soldier = new UnitToken(HEGEMONY, "Soldier", mainUnitAttributes);
  UnitToken* anotherSoldier = new UnitToken(HEGEMONY, "UniversalSoldier", mainUnitAttributes);
  ASSERT_TRUE(module -> boardTokens.empty());
  module -> addBoardToken(unit);
  module -> addBoardToken(soldier);
  module -> addBoardToken(anotherSoldier);
  EXPECT_EQ(3, module -> boardTokens.size());
  EXPECT_EQ("Soldier", module -> boardTokens[1] -> getName());
  module -> removeBoardToken(soldier);
  EXPECT_EQ(2, module -> boardTokens.size());
  EXPECT_EQ("UniversalSoldier", module -> boardTokens[1] -> getName());
  module -> removeBoardToken(anotherSoldier);
  EXPECT_EQ(1, module -> boardTokens.size());
  EXPECT_EQ("UniversalSoldier", module -> boardTokens[0] -> getName());
  EXPECT_EQ(unit, module -> boardTokens[0]);
  delete module;
}

TEST_F(ModuleTokenTest, shouldUpgradeBaseAttribute) {
  int oldInitiativeValue = unit -> getAttribute(INITIATIVE) -> getValue();
  ASSERT_EQ(2, oldInitiativeValue);
  Module* ranger = new ChangeAttributeUpgrader(new ModuleToken(HEGEMONY, "Ranger", mainModuleAttributes, activeEdges), INITIATIVE, 1);
  ranger -> addBoardToken(unit);
  int newInitiativeValue = unit -> getAttribute(INITIATIVE) -> getValue();
  ASSERT_EQ(3, newInitiativeValue);
}

TEST_F(ModuleTokenTest, shouldDowngradeAttributeOnRemove) {
  Module* ranger = new ChangeAttributeUpgrader(new ModuleToken(HEGEMONY, "Ranger", mainModuleAttributes, activeEdges), INITIATIVE, 1);
  ranger -> addBoardToken(unit);
  int attributeValue = unit -> getAttribute(INITIATIVE) -> getValue();
  EXPECT_EQ(3, attributeValue);
  ranger -> removeBoardToken(unit);
  attributeValue = unit -> getAttribute(INITIATIVE) -> getValue();
  EXPECT_EQ(2, attributeValue);
}

TEST_F(ModuleTokenTest, shouldUpgradeEdgeAttribute) {
  Module* officer = new ChangeAttributeUpgrader(new ModuleToken(HEGEMONY, "Officer", mainModuleAttributes, activeEdges), MELEE, 1);
  Attribute* melee = unit -> getEdgeAttributes(NORTH) -> getAttribute(MELEE);
  int oldMeleeValue = melee -> getValue();
  ASSERT_EQ(1, oldMeleeValue);
  officer -> addBoardToken(unit);
  int newMeleeValue = melee -> getValue();
  ASSERT_EQ(2, newMeleeValue);
}

TEST_F(ModuleTokenTest, shouldAddAttribute) {
  Module* transport = new AddAttributeUpgrader(new ModuleToken(HEGEMONY, "Transport", mainModuleAttributes, activeEdges), MOBILITY, "mobility");
  Attribute* unitAttribute = unit -> getAttribute(MOBILITY);
  EXPECT_EQ(0, unitAttribute);
  transport -> addBoardToken(unit);
  unitAttribute = unit -> getAttribute(MOBILITY);
  ASSERT_NE((Attribute*) 0, unitAttribute);
  int mobilityValue = unit -> getAttribute(MOBILITY) -> getValue();
  ASSERT_EQ(1, mobilityValue);
}

TEST_F(ModuleTokenTest, shouldDowngradeEnemyAttribute) {
  Attribute* initiative = unit -> getAttribute(INITIATIVE);
  ASSERT_NE((Attribute*) 0, initiative);
  int oldInitiativeValue = initiative -> getValue();
  ASSERT_EQ(2, oldInitiativeValue);
  Module* saboteur = new ChangeAttributeUpgrader(new ModuleToken(OUTPOST, "Saboteur", mainModuleAttributes, activeEdges), INITIATIVE, -1);
  saboteur -> addBoardToken(unit);
  int newInitiativeValue = unit -> getAttribute(INITIATIVE) -> getValue();
  ASSERT_EQ(1, newInitiativeValue);
}

TEST_F(ModuleTokenTest, shouldCaptureEnemyModule) {
  Module* scoper = new ChangeArmyUpgrader(new ModuleToken(OUTPOST, "Scoper", mainModuleAttributes, activeEdges));
  EXPECT_EQ(HEGEMONY, unit -> getArmy());
  scoper -> addBoardToken(unit);
  ASSERT_EQ(OUTPOST, unit -> getArmy());
  scoper -> removeBoardToken(unit);
  EXPECT_EQ(HEGEMONY, unit -> getArmy());
  UnitToken* anotherUnit = new UnitToken(MOLOCH, "Gauss cannon", mainUnitAttributes);
  anotherUnit -> setEdgeAttributes(NORTH, northSideAttributes);
  EXPECT_EQ(MOLOCH, anotherUnit -> getArmy());
  scoper -> addBoardToken(anotherUnit);
  ASSERT_EQ(OUTPOST, anotherUnit -> getArmy());
}

TEST_F(ModuleTokenTest, shouldApplyTwoDifferentUpgradesFromOneModule) {
  Module* boss = new ChangeAttributeUpgrader(new ChangeAttributeUpgrader(new ModuleToken(HEGEMONY, "Boss", mainModuleAttributes, activeEdges), MELEE, 1), INITIATIVE, 2);
  ASSERT_EQ(1, unit -> getEdgeAttributes(NORTH) -> getAttribute(MELEE) -> getValue());
  ASSERT_EQ(2, unit -> getAttribute(INITIATIVE) -> getValue());

  boss -> addBoardToken(unit);

  ASSERT_EQ(2, unit -> getEdgeAttributes(NORTH) -> getAttribute(MELEE) -> getValue());
  ASSERT_EQ(4, unit -> getAttribute(INITIATIVE) -> getValue());
}


//TODO: create mocks
class InstantTokenTest : public Test
{
protected:
  InstantTokenTest(void) {
    model = new Model();
    controller = new Controller(model);
  }
  ~InstantTokenTest(void) {
    delete controller;
    delete model;
  }

  virtual void SetUp(void) {}
  virtual void TearDown(void) {}

  BoardToken* createBoardTokenWithToughness();

  Model* model;
  Controller* controller;
};

BoardToken* InstantTokenTest::createBoardTokenWithToughness() {
  Attribute* toughness = new Attribute("toughness", 2);
  BoardToken* token = new BoardToken(MOLOCH, "soldier");
  token -> addAttribute(TOUGHNESS, toughness);
  return token;
}

TEST_F(InstantTokenTest, shouldCauseBattle) {
  BattleToken* battle = new BattleToken(MOLOCH, controller);
  ASSERT_EQ(PAUSE, model -> getGameState());
  battle -> action();
  EXPECT_EQ(BATTLE, model -> getGameState());
  delete battle;
}

TEST_F(InstantTokenTest, shouldMoveToken) {
  MovementToken* movement = new MovementToken(MOLOCH, controller);
  BoardToken* token = new BoardToken(MOLOCH, "soldier");
  Field* field = new Field;
  Field* destination = new Field;
  token -> setField(field);
  movement -> setTokenToMove(token);
  movement -> setDestination(destination);
  movement -> action();
  EXPECT_NE(field, token -> getField());
  EXPECT_EQ(NULL, field -> getToken());
  EXPECT_EQ(destination, token -> getField());
  EXPECT_EQ(token, destination -> getToken());
  delete field;
  delete movement;
}

TEST_F(InstantTokenTest, shouldPushToken) {
  PushToken* push = new PushToken(MOLOCH, controller);
  BoardToken* pusher = new BoardToken(MOLOCH, "soldier");
  BoardToken* pushee = new BoardToken(OUTPOST, "soldier");
  Field* pusherField = new Field;
  Field* pusheeField = new Field;
  Field* destination = new Field;
  pusher -> setField(pusherField);
  pushee -> setField(pusheeField);
  push -> setPushingToken(pusher);
  push -> setPushedToken(pushee);
  push -> setDestination(destination);
  push -> action();
  EXPECT_NE(pusheeField, pushee -> getField());
  EXPECT_EQ(destination, pushee -> getField());
  EXPECT_EQ(pushee, destination -> getToken());
  delete pusherField;
  delete pusheeField;
  delete pusher;
  delete pushee;
  delete push;
}

TEST_F(InstantTokenTest, shouldBombStrikeField) {
  BombToken* bomb = new BombToken(MOLOCH, controller);
  BoardToken* firstToken = createBoardTokenWithToughness();
  BoardToken* secondToken = createBoardTokenWithToughness();
  Field* firstField = new Field;
  Field* secondField = new Field;
  firstField -> addNeighbour(secondField, NORTH);
  firstField -> setToken(firstToken);
  firstToken -> setField(firstField);
  secondField -> addNeighbour(firstField, SOUTH);
  secondField -> setToken(secondToken);
  secondToken -> setField(secondField);

  bomb -> setEpicentrum(firstToken -> getField());
  bomb -> action();
  EXPECT_EQ(1, firstToken -> getAttribute(TOUGHNESS) -> getValue());
  EXPECT_EQ(1, secondToken -> getAttribute(TOUGHNESS) -> getValue());
  delete firstField;
  delete secondField;
  delete bomb;
}

TEST_F(InstantTokenTest, shouldDestroyToken) {
  GranadeToken* granade = new GranadeToken(BORGO, controller);
  Player* player = new Player(MOLOCH);
  model -> addPlayer(player);
  BoardToken* token = new BoardToken(MOLOCH, "soldier");
  Field* field = new Field;
  token -> setField(field);
  field -> setToken(token);
  granade -> setTokenToDestroy(token);
  granade -> action();
//  ASSERT_FALSE(model -> usedTokens.empty());
//  EXPECT_EQ(token, model -> usedTokens[0]);
  delete token;
  delete granade;
}

TEST_F(InstantTokenTest, shouldStrikeToken) {
  SniperToken* sniper = new SniperToken(OUTPOST, controller);
  BoardToken* token = createBoardTokenWithToughness();
  sniper -> setTokenToStrike(token);
  sniper -> action();
  EXPECT_EQ(1, token -> getAttribute(TOUGHNESS) -> getValue());
  delete sniper;
}
