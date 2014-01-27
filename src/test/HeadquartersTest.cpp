#include <gmock/gmock.h>
using ::testing::Eq;
#include <gtest/gtest.h>
using ::testing::Test;

#include "logic/HeadquartersToken.hpp"
#include "logic/ChangeAttributeUpgrader.hpp"
#include "logic/AddAttributeUpgrader.hpp"

class HeadquartersTest : public Test
{
protected:
  HeadquartersTest(void) {
    hq = new HeadquartersToken(HEGEMONY, "HQ", NULL);
  }
  ~HeadquartersTest(void) {
    delete hq;
  }
  virtual void SetUp(void) {}
  virtual void TearDown(void) {}

  HeadquartersToken* hq;
};

TEST_F(HeadquartersTest, shouldHaveAllEdgesActiveByDefault) {
  for (int i=0; i<6; ++i) {
    EXPECT_TRUE(hq -> isEdgeActive((Side) i));
  }
}

TEST_F(HeadquartersTest, shouldHaveInitiativeZeroByDefault) {
  Attribute* initiative = hq -> UnitToken::getAttribute(INITIATIVE);
  ASSERT_NE((Attribute*) NULL, initiative);
  EXPECT_EQ(0, initiative -> getValue());
}

TEST_F(HeadquartersTest, shouldAttackInAllDirections) {
  for (int i=0; i<6; ++i) {
    EXPECT_EQ(1, hq -> getEdgeAttributes((Side) i) -> getAttribute(MELEE) -> getValue());
  }
}

TEST_F(HeadquartersTest, shouldUpgradeBoardTokenBaseAttribute) {
  Module* borgoHQ = new ChangeAttributeUpgrader(hq, INITIATIVE, 1);
  BoardToken* token = new BoardToken(BORGO, "token", new Attributes);
  Attribute* initiative = new Attribute("initiative", 1);
  token -> addAttribute(INITIATIVE, initiative);
  borgoHQ -> addBoardToken(token);
  EXPECT_EQ(2, token -> getAttribute(INITIATIVE) -> getValue());
}

TEST_F(HeadquartersTest, shouldUpgradeUnitTokenEdgeAttribute) {
  Module* hegemonyHQ = new ChangeAttributeUpgrader(hq, MELEE, 1);
  UnitToken* token = new UnitToken(HEGEMONY, "token", new Attributes);
  Attribute* melee = new Attribute("melee", 1);
  Attributes* northEdgeAttributes = new Attributes;
  northEdgeAttributes -> addAttribute(MELEE, melee);
  token -> setEdgeAttributes(NORTH, northEdgeAttributes);
  hegemonyHQ -> addBoardToken(token);
  EXPECT_EQ(2, token -> getEdgeAttributes(NORTH) -> getAttribute(MELEE) -> getValue());
}

TEST_F(HeadquartersTest, shouldAddAttributeToUnit) {
  Module* outpostHQ = new AddAttributeUpgrader(hq, MOTHER, "mother");
  BoardToken* token = new BoardToken(OUTPOST, "token", new Attributes);
  outpostHQ -> addBoardToken(token);
  ASSERT_NE((Attribute*) NULL, token -> getAttribute(MOTHER));
  EXPECT_EQ(1, token -> getAttribute(MOTHER) -> getValue());
}
