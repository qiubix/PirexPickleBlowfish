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
  ASSERT_EQ("initiative", attribute->getName());
  ASSERT_EQ(ATTRIBUTE_VALUE, attribute->getValue());
}

TEST_F(AttributeTest, testUpgradeAttribute) {
  attribute->upgradeBy();
  int upgradedValue = ATTRIBUTE_VALUE + 1;
  ASSERT_EQ(upgradedValue, attribute->getValue());
  attribute->upgradeBy(2);
  upgradedValue += 2;
  ASSERT_EQ(upgradedValue, attribute->getValue());
  attribute->upgradeTo(ATTRIBUTE_VALUE);
  ASSERT_EQ(ATTRIBUTE_VALUE, attribute->getValue());
}

TEST_F(AttributeTest, testDowngradeAttribute) {
  attribute->downgradeBy();
  int downgradedValue = ATTRIBUTE_VALUE - 1;
  ASSERT_EQ(downgradedValue, attribute->getValue());
  attribute->downgradeBy(2);
  downgradedValue -= 2;
  ASSERT_EQ(downgradedValue, attribute->getValue());
  attribute->downgradeTo();
  ASSERT_EQ(ATTRIBUTE_VALUE, attribute->getValue());
  downgradedValue = ATTRIBUTE_VALUE - 1;
  attribute->downgradeTo(ATTRIBUTE_VALUE-1);
  ASSERT_EQ(downgradedValue, attribute->getValue());
}

class BoardTokenTest : public Test
{
protected:
  BoardTokenTest() {
    Attributes* attributes = new Attributes;
    initiative = new Attribute("initiative", ATTRIBUTE_VALUE);
    attributes->addAttribute(INITIATIVE, initiative);
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
  Attribute* attribute = token->getAttribute(INITIATIVE);
  ASSERT_EQ(initiative, attribute);
  ASSERT_EQ(initiative->getName(), attribute->getName());
  ASSERT_EQ(initiative->getValue(), attribute->getValue());
}

TEST_F(BoardTokenTest, testModifyAttribute) {
  token->upgradeAttributeBy(INITIATIVE);
  ASSERT_EQ(ATTRIBUTE_VALUE + 1, token->getAttribute(INITIATIVE)->getValue());
  token->downgradeAttributeBy(INITIATIVE);
  ASSERT_EQ(ATTRIBUTE_VALUE, token->getAttribute(INITIATIVE)->getValue());
}

TEST_F(BoardTokenTest, testRemoveAttribute) {
  ASSERT_EQ(1, token->getAttributes()->attributes.size());
  token->removeAttribute(INITIATIVE);
  ASSERT_EQ(0, token->getAttributes()->attributes.size());
}

TEST_F(BoardTokenTest, testGetOrientation) {
  ASSERT_EQ(NORTH, token->getOrientation());
}

TEST_F(BoardTokenTest, testSetOrientation) {
  token->setOrientation(SOUTH);
  ASSERT_EQ(SOUTH, token->getOrientation());
}

TEST_F(BoardTokenTest, testRotateClockwise) {
  token->setOrientation(SOUTH);
  token->rotateClockwise();
  ASSERT_EQ(SOUTH_WEST, token->getOrientation());
}

TEST_F(BoardTokenTest, testRotateAnticlockwise) {
  token->setOrientation(SOUTH);
  token->rotateAnticlockwise();
  ASSERT_EQ(SOUTH_EAST, token->getOrientation());
}


class UnitTokenTest : public Test
{
protected:
  UnitTokenTest() {
    northSideAttributes = new Attributes;
    Attribute* melee = new Attribute("melee", 1);
    northSideAttributes->addAttribute(MELEE, melee);
    sideAttributes[NORTH] = northSideAttributes;
    baseUnitAttributes = new Attributes;
    unit = new UnitToken(HEGEMONY, "UniversalSoldier", baseUnitAttributes, sideAttributes);
  }
  ~UnitTokenTest() {}
  void SetUp() {}
  void TearDown() {}

  UnitToken* unit;
  Attributes* baseUnitAttributes;
  Attributes* sideAttributes[6];
  Attributes* northSideAttributes;
};

TEST_F(UnitTokenTest, testGetSideAttributes) {
  Attributes* attributes = unit->getEdgeAttributes(NORTH);
  Attribute* melee = northSideAttributes->getAttribute(MELEE);
  ASSERT_EQ(northSideAttributes, attributes);
  ASSERT_EQ(melee, attributes->getAttribute(MELEE));
  ASSERT_EQ(melee->getValue(), attributes->getAttribute(MELEE)->getValue());
}


class ModuleTokenTest : public Test
{
protected:
  ModuleTokenTest() {
    initiative = new Attribute("initiative", 2);
    mainUnitAttributes = new Attributes;
    mainUnitAttributes->addAttribute(INITIATIVE, initiative);
    melee = new Attribute("melee", 1);
    northSideAttributes = new Attributes;
    northSideAttributes -> addAttribute(MELEE, melee);
    //TODO: this should be done in Attributes constructor
    for(int i=0; i<6; ++i) {
      sideAttributes[i] = NULL;
    }
    sideAttributes[NORTH] = northSideAttributes;
    unit = new UnitToken(HEGEMONY, "UniversalSoldier", mainUnitAttributes, sideAttributes);
    toughness = new Attribute("toughness", 1);
    mainModuleAttributes = new Attributes;
    mainModuleAttributes->addAttribute(TOUGHNESS, toughness);
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
  Attributes* sideAttributes[6];
  UnitToken* unit;
  Attribute* toughness;
  Attributes* mainModuleAttributes;
  std::vector<Side> activeEdges;
};

TEST_F(ModuleTokenTest, shouldNotAffectEnemiesOnDefault) {
  Upgrader* upgrader = new ChangeAttributeUpgrader(new ModuleToken(HEGEMONY, "Officer", mainModuleAttributes, activeEdges), MELEE, 1);
  ASSERT_FALSE(upgrader -> isAffectingEnemies());
}

TEST_F(ModuleTokenTest, shouldAffectEnemies) {
  Upgrader* upgrader = new ChangeAttributeUpgrader(new ModuleToken(HEGEMONY, "Officer", mainModuleAttributes, activeEdges), MELEE, 1, true);
  ASSERT_TRUE(upgrader -> isAffectingEnemies());
}

//FIXME: make tests more in-depth and more clear
TEST_F(ModuleTokenTest, testUpgradeAttribute) {
  Module* officer = new ChangeAttributeUpgrader(new ModuleToken(HEGEMONY, "Officer", mainModuleAttributes, activeEdges), MELEE, 1);
  officer->addBoardToken(unit);
  Attribute* melee = unit->getEdgeAttributes(NORTH)->getAttribute(MELEE);
  int newMeleeValue = melee->getValue();
  ASSERT_EQ(2, newMeleeValue);
  int oldInitiativeValue = unit->getAttribute(INITIATIVE)->getValue();
  ASSERT_EQ(2, oldInitiativeValue);
  Module* ranger = new ChangeAttributeUpgrader(new ModuleToken(HEGEMONY, "Ranger", mainModuleAttributes, activeEdges), INITIATIVE, 1);
  ranger->addBoardToken(unit);
  int newInitiativeValue = unit->getAttribute(INITIATIVE)->getValue();
  ASSERT_EQ(3, newInitiativeValue);
}

TEST_F(ModuleTokenTest, testAddAttribute) {
  Module* transport = new AddAttributeUpgrader(new ModuleToken(HEGEMONY, "Transport", mainModuleAttributes, activeEdges),
                                               MOBILITY,
                                               "mobility");
  transport->addBoardToken(unit);
  Attribute* unitAttribute = unit->getAttribute(MOBILITY);
  ASSERT_NE((Attribute*) 0, unitAttribute);
  int mobilityValue = unit->getAttribute(MOBILITY)->getValue();
  ASSERT_EQ(1, mobilityValue);
}

TEST_F(ModuleTokenTest, testDowngradeEnemyAttribute) {
  Attribute* initiative = unit->getAttribute(INITIATIVE);
  ASSERT_NE((Attribute*) 0, initiative);
  int oldInitiativeValue = initiative->getValue();
  ASSERT_EQ(2, oldInitiativeValue);
  Module* saboteur = new ChangeAttributeUpgrader(new ModuleToken(OUTPOST, "Saboteur", mainModuleAttributes, activeEdges), INITIATIVE, -1);
  saboteur->addBoardToken(unit);
  int newInitiativeValue = unit->getAttribute(INITIATIVE)->getValue();
  ASSERT_EQ(1, newInitiativeValue);
}

TEST_F(ModuleTokenTest, testCaptureEnemyModule) {
  Module* scoper = new ChangeArmyUpgrader(new ModuleToken(OUTPOST, "Scoper", mainModuleAttributes, activeEdges));
  scoper->addBoardToken(unit);
  Army newUnitAffiliation = unit->getArmy();
  ASSERT_EQ(OUTPOST, newUnitAffiliation);
  UnitToken* anotherUnit = new UnitToken(MOLOCH, "Gauss cannon", mainUnitAttributes, sideAttributes);
  scoper->addBoardToken(anotherUnit);
  newUnitAffiliation = anotherUnit->getArmy();
  ASSERT_EQ(OUTPOST, newUnitAffiliation);
}

TEST_F(ModuleTokenTest, shouldApplyTwoDifferentUpgradesFromOneModule) {
  Module* boss = new ChangeAttributeUpgrader(new ChangeAttributeUpgrader(new ModuleToken(HEGEMONY, "Boss", mainModuleAttributes, activeEdges), MELEE, 1), INITIATIVE, 2);
  ASSERT_EQ(1, unit -> getEdgeAttributes(NORTH) -> getAttribute(MELEE) -> getValue());
  ASSERT_EQ(2, unit -> getAttribute(INITIATIVE) -> getValue());

  boss -> addBoardToken(unit);

  ASSERT_EQ(2, unit -> getEdgeAttributes(NORTH) -> getAttribute(MELEE) -> getValue());
  ASSERT_EQ(4, unit -> getAttribute(INITIATIVE) -> getValue());
}
