#include <gmock/gmock.h>
using ::testing::Eq;
#include <gtest/gtest.h>
using ::testing::Test;

#include <cstdlib>
#include <vector>
#include "../src/logic/ModuleToken.hpp"
#include "../src/logic/UnitToken.hpp"
#include "../src/logic/Upgrader.hpp"
#include "../src/logic/AddAttributeUpgrader.hpp"
#include "../src/logic/ChangeArmyUpgrader.hpp"
#include "../src/logic/ChangeAttributeUpgrader.hpp"

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
    unit = new UnitToken(Army::HEGEMONY, "UniversalSoldier", mainUnitAttributes);
    unit -> setEdgeAttributes(Side::NORTH, northSideAttributes);
    toughness = new Attribute("toughness", 1);
    mainModuleAttributes = new Attributes;
    mainModuleAttributes -> addAttribute(TOUGHNESS, toughness);
    activeEdges.push_back(Side::NORTH);
    activeEdges.push_back(Side::SOUTH);
  }
  ~ModuleTokenTest() {
    delete unit;
  }

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
  Upgrader* upgrader = new ChangeAttributeUpgrader(new ModuleToken(Army::HEGEMONY, "Officer", mainModuleAttributes, activeEdges), MELEE, 1);
  ASSERT_FALSE(upgrader->isAffectingEnemies());
}

TEST_F(ModuleTokenTest, shouldAffectEnemies) {
  Upgrader* upgrader = new ChangeAttributeUpgrader(new ModuleToken(Army::HEGEMONY, "Officer", mainModuleAttributes, activeEdges), MELEE, 1, true);
  ASSERT_TRUE(upgrader->isAffectingEnemies());
}

TEST_F(ModuleTokenTest, shouldAddBoardToken) {
  ModuleToken* module = new ModuleToken(Army::HEGEMONY, "Officer", mainModuleAttributes, activeEdges);
  EXPECT_TRUE(module -> boardTokens.empty());
  module -> addBoardToken(unit);
  EXPECT_EQ(1, module -> boardTokens.size());
  EXPECT_EQ("UniversalSoldier", module->boardTokens[0]->getName());
  delete module;
}

TEST_F(ModuleTokenTest, shouldRemoveBoardToken) {
  ModuleToken* module = new ModuleToken(Army::HEGEMONY, "Officer", mainModuleAttributes, activeEdges);
  UnitToken* soldier = new UnitToken(Army::HEGEMONY, "Soldier", mainUnitAttributes);
  UnitToken* anotherSoldier = new UnitToken(Army::HEGEMONY, "UniversalSoldier", mainUnitAttributes);
  ASSERT_TRUE(module -> boardTokens.empty());
  module -> addBoardToken(unit);
  module -> addBoardToken(soldier);
  module -> addBoardToken(anotherSoldier);
  EXPECT_EQ(3, module -> boardTokens.size());
  EXPECT_EQ("Soldier", module->boardTokens[1]->getName());
  module -> removeBoardToken(soldier);
  EXPECT_EQ(2, module -> boardTokens.size());
  EXPECT_EQ("UniversalSoldier", module->boardTokens[1]->getName());
  module -> removeBoardToken(anotherSoldier);
  EXPECT_EQ(1, module -> boardTokens.size());
  EXPECT_EQ("UniversalSoldier", module->boardTokens[0]->getName());
  EXPECT_EQ(unit, module -> boardTokens[0]);
  delete module;
}

TEST_F(ModuleTokenTest, shouldUpgradeBaseAttribute) {
  int oldInitiativeValue = unit->getAttribute(INITIATIVE)->getValue();
  ASSERT_EQ(2, oldInitiativeValue);
  Module* ranger = new ChangeAttributeUpgrader(new ModuleToken(Army::HEGEMONY, "Ranger", mainModuleAttributes, activeEdges), INITIATIVE, 1);
  ranger -> addBoardToken(unit);
  int newInitiativeValue = unit->getAttribute(INITIATIVE)->getValue();
  ASSERT_EQ(3, newInitiativeValue);
}

TEST_F(ModuleTokenTest, shouldDowngradeAttributeOnRemove) {
  Module* ranger = new ChangeAttributeUpgrader(new ModuleToken(Army::HEGEMONY, "Ranger", mainModuleAttributes, activeEdges), INITIATIVE, 1);
  ranger -> addBoardToken(unit);
  int attributeValue = unit->getAttribute(INITIATIVE)->getValue();
  EXPECT_EQ(3, attributeValue);
  ranger -> removeBoardToken(unit);
  attributeValue = unit->getAttribute(INITIATIVE)->getValue();
  EXPECT_EQ(2, attributeValue);
}

TEST_F(ModuleTokenTest, shouldUpgradeEdgeAttribute) {
  Module* officer = new ChangeAttributeUpgrader(new ModuleToken(Army::HEGEMONY, "Officer", mainModuleAttributes, activeEdges), MELEE, 1);
  Attribute* melee = unit -> getEdgeAttributes(Side::NORTH) -> getAttribute(MELEE);
  int oldMeleeValue = melee->getValue();
  ASSERT_EQ(1, oldMeleeValue);
  officer -> addBoardToken(unit);
  int newMeleeValue = melee->getValue();
  ASSERT_EQ(2, newMeleeValue);
}

TEST_F(ModuleTokenTest, shouldAddAttribute) {
  Module* transport = new AddAttributeUpgrader(new ModuleToken(Army::HEGEMONY, "Transport", mainModuleAttributes, activeEdges), MOBILITY, "mobility");
  Attribute* unitAttribute = unit -> getAttribute(MOBILITY);
  EXPECT_EQ(0, unitAttribute);
  transport -> addBoardToken(unit);
  unitAttribute = unit -> getAttribute(MOBILITY);
  ASSERT_NE((Attribute*) 0, unitAttribute);
  int mobilityValue = unit->getAttribute(MOBILITY)->getValue();
  ASSERT_EQ(1, mobilityValue);
}

TEST_F(ModuleTokenTest, shouldDowngradeEnemyAttribute) {
  Attribute* initiative = unit -> getAttribute(INITIATIVE);
  ASSERT_NE((Attribute*) 0, initiative);
  int oldInitiativeValue = initiative->getValue();
  ASSERT_EQ(2, oldInitiativeValue);
  Module* saboteur = new ChangeAttributeUpgrader(new ModuleToken(Army::OUTPOST, "Saboteur", mainModuleAttributes, activeEdges), INITIATIVE, -1);
  saboteur -> addBoardToken(unit);
  int newInitiativeValue = unit->getAttribute(INITIATIVE)->getValue();
  ASSERT_EQ(1, newInitiativeValue);
}

TEST_F(ModuleTokenTest, shouldCaptureEnemyModule) {
  Module* scoper = new ChangeArmyUpgrader(new ModuleToken(Army::OUTPOST, "Scoper", mainModuleAttributes, activeEdges));
  EXPECT_EQ(Army::HEGEMONY, unit->getArmy());
  scoper -> addBoardToken(unit);
  ASSERT_EQ(Army::OUTPOST, unit->getArmy());
  scoper -> removeBoardToken(unit);
  EXPECT_EQ(Army::HEGEMONY, unit->getArmy());
  UnitToken* anotherUnit = new UnitToken(Army::MOLOCH, "Gauss cannon", mainUnitAttributes);
  anotherUnit -> setEdgeAttributes(Side::NORTH, northSideAttributes);
  EXPECT_EQ(Army::MOLOCH, anotherUnit->getArmy());
  scoper -> addBoardToken(anotherUnit);
  ASSERT_EQ(Army::OUTPOST, anotherUnit->getArmy());
}

TEST_F(ModuleTokenTest, shouldApplyTwoDifferentUpgradesFromOneModule) {
  Module* boss = new ChangeAttributeUpgrader(new ChangeAttributeUpgrader(new ModuleToken(Army::HEGEMONY, "Boss", mainModuleAttributes, activeEdges), MELEE, 1), INITIATIVE, 2);
  ASSERT_EQ(1, unit->getEdgeAttributes(Side::NORTH)->getAttribute(MELEE)->getValue());
  ASSERT_EQ(2, unit->getAttribute(INITIATIVE)->getValue());

  boss -> addBoardToken(unit);

  ASSERT_EQ(2, unit->getEdgeAttributes(Side::NORTH)->getAttribute(MELEE)->getValue());
  ASSERT_EQ(4, unit->getAttribute(INITIATIVE)->getValue());
}
