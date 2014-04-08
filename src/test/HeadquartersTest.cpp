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

//REVIEW: TODO: refactor all such loops to for(Side side = NORTH; side <= NORTH_WEST; side++)
TEST_F(HeadquartersTest, shouldHaveAllEdgesActiveByDefault) {
//  for (int i=0; i<6; ++i) {
//  for (Side side = Side::NORTH; side <= Side::NORTH_WEST; ++side) {
	Side side = Side::NORTH;
	do {
		EXPECT_TRUE(hq -> isEdgeActive(side));
		++side;
	} while (side != Side::NORTH);
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
  Module* borgoHQ = new ChangeAttributeUpgrader(new HeadquartersToken(BORGO, "HQ", NULL), INITIATIVE, 1);
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
  Module* outpostHQ = new AddAttributeUpgrader(new HeadquartersToken(OUTPOST, "HQ", NULL), MOTHER, "mother");
  BoardToken* token = new BoardToken(OUTPOST, "token", new Attributes);
  outpostHQ -> addBoardToken(token);
  ASSERT_NE((Attribute*) NULL, token -> getAttribute(MOTHER));
  EXPECT_EQ(1, token -> getAttribute(MOTHER) -> getValue());
}
