#include <gmock/gmock.h>
using ::testing::Eq;
#include <gtest/gtest.h>
using ::testing::Test;

#include "logic/Attribute.hpp"
#include "logic/BoardToken.hpp"
#include "logic/UnitToken.hpp"
#include "logic/ModuleToken.hpp"

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
  attribute->upgrade();
  int upgradedValue = ATTRIBUTE_VALUE + 1;
  ASSERT_EQ(upgradedValue, attribute->getValue());
  attribute->upgrade(2);
  upgradedValue += 2;
  ASSERT_EQ(upgradedValue, attribute->getValue());
}

TEST_F(AttributeTest, testDowngradeAttribute) {
  attribute->downgrade();
  int downgradedValue = ATTRIBUTE_VALUE - 1;
  ASSERT_EQ(downgradedValue, attribute->getValue());
  attribute->downgrade(2);
  downgradedValue -= 2;
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
  token->upgradeAttribute(INITIATIVE);
  ASSERT_EQ(ATTRIBUTE_VALUE + 1, token->getAttribute(INITIATIVE)->getValue());
  token->downgradeAttribute(INITIATIVE);
  ASSERT_EQ(ATTRIBUTE_VALUE, token->getAttribute(INITIATIVE)->getValue());
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
    unit = new UnitToken(HEGEMONY, "UniversalSoldier", NULL, sideAttributes);
  }
  ~UnitTokenTest() {}
  void SetUp() {}
  void TearDown() {}

  UnitToken* unit;
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
    initiative = new Attribute("initiative", 1);
    mainUnitAttributes = new Attributes;
    mainUnitAttributes->addAttribute(INITIATIVE, initiative);
    melee = new Attribute("melee", 1);
    northSideAttributes = new Attributes;
    northSideAttributes->addAttribute(MELEE, melee);
    sideAttributes[NORTH] = northSideAttributes;
    unit = new UnitToken(HEGEMONY, "UniversalSoldier", mainUnitAttributes, sideAttributes);
    toughness = new Attribute("toughness", 1);
    mainModuleAttributes = new Attributes;
    mainModuleAttributes->addAttribute(TOUGHNESS, toughness);
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
};

TEST_F(ModuleTokenTest, testUpgradeAttribute) {
  ModuleToken* officer = new ModuleToken(HEGEMONY, "Officer", mainModuleAttributes);
  officer->addBoardToken(unit);
  Attribute* melee = unit->getEdgeAttributes(NORTH)->getAttribute(MELEE);
  int newMeleeValue = melee->getValue();
  ASSERT_EQ(2, newMeleeValue);
  ModuleToken* ranger = new ModuleToken(HEGEMONY, "Ranger", mainModuleAttributes);
  ranger->addBoardToken(unit);
  int newInitiativeValue = unit->getEdgeAttributes(NORTH)->getAttribute(INITIATIVE)->getValue();
  ASSERT_EQ(2, newInitiativeValue);
}

TEST_F(ModuleTokenTest, testAddAttribute) {
  ModuleToken* transport = new ModuleToken(HEGEMONY, "Transport", mainModuleAttributes);
  transport->addBoardToken(unit);
  Attribute* mobility = unit->getAttribute(MOBILITY);
  ASSERT_NE((Attribute*) 0, mobility);
  int mobilityValue = unit->getAttribute(MOBILITY)->getValue();
  ASSERT_EQ(1, mobilityValue);
}

TEST_F(ModuleTokenTest, testDowngradeEnemyAttribute) {
  Attribute* initiative = unit->getAttribute(INITIATIVE);
  ASSERT_NE((Attribute*) 0, initiative);
  int oldInitiativeValue = initiative->getValue();
  ASSERT_EQ(2, oldInitiativeValue);
  ModuleToken* saboteur = new ModuleToken(OUTPOST, "Saboteur", mainModuleAttributes);
  saboteur->addBoardToken(unit);
  int newInitiativeValue = unit->getAttribute(INITIATIVE)->getValue();
  ASSERT_EQ(1, newInitiativeValue);
}

TEST_F(ModuleTokenTest, testCaptureEnemyModule) {
  ModuleToken* scoper = new ModuleToken(OUTPOST, "Scoper", mainModuleAttributes);
  scoper->addBoardToken(unit);
  Army newUnitAffiliation = unit->getArmy();
  ASSERT_EQ(OUTPOST, newUnitAffiliation);
}
