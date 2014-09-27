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
    hq = new HeadquartersToken(HEGEMONY, "HQ", nullptr);
  }
  ~HeadquartersTest(void) {
    delete hq;
  }
  virtual void SetUp(void) {}
  virtual void TearDown(void) {}

  HeadquartersToken* hq;
};

TEST_F(HeadquartersTest, shouldHaveAllEdgesActiveByDefault) {
  Side side = Side::NORTH;
  //TODO: custom matcher from gmock https://code.google.com/p/googlemock/wiki/V1_7_CookBook#Writing_New_Matchers_Quickly
  do {
    EXPECT_TRUE(hq -> isEdgeActive(side));
    ++side;
  } while (side != Side::NORTH);
}

TEST_F(HeadquartersTest, shouldHaveInitiativeZeroByDefault) {
  Attribute* initiative = hq -> UnitToken::getAttribute(INITIATIVE);
  ASSERT_NE(nullptr, initiative);
  EXPECT_EQ(0, initiative -> getValue());
}

TEST_F(HeadquartersTest, shouldAttackInAllDirections) {
  Side side = Side::NORTH;
  do {
    EXPECT_EQ(1, hq -> getEdgeAttributes(side) -> getAttribute(MELEE) -> getValue());
  } while (side != Side::NORTH);
}

TEST_F(HeadquartersTest, shouldUpgradeBoardTokenBaseAttribute) {
  Module* borgoHQ = new ChangeAttributeUpgrader(new HeadquartersToken(BORGO, "HQ", nullptr), INITIATIVE, 1);
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
  token -> setEdgeAttributes(Side::NORTH, northEdgeAttributes);
  hegemonyHQ -> addBoardToken(token);
  EXPECT_EQ(2, token -> getEdgeAttributes(Side::NORTH) -> getAttribute(MELEE) -> getValue());
}

TEST_F(HeadquartersTest, shouldAddAttributeToBoardToken) {
  Module* outpostHQ = new AddAttributeUpgrader(new HeadquartersToken(OUTPOST, "HQ", nullptr), MOTHER, "mother");
  BoardToken* token = new BoardToken(OUTPOST, "token", new Attributes);
  outpostHQ -> addBoardToken(token);
  ASSERT_NE(nullptr, token -> getAttribute(MOTHER));
  EXPECT_EQ(1, token -> getAttribute(MOTHER) -> getValue());
}
