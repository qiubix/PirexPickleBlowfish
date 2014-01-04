#include <gmock/gmock.h>
using ::testing::Eq;
#include <gtest/gtest.h>
using ::testing::Test;

//REVIEW: maybe having all tested includes in test file is not a bad idea.
#include "logic/Unit.hpp"

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


class UnitTest : public Test
{
protected:
  UnitTest() {
    //REVIEW: this setup is very long
    //REVIEW: do you need attributes somewhere in test or we can just erase these 3 lines and pass NULL to constructor?
    Attributes* attributes = new Attributes;
    Attribute* initiative = new Attribute("initiative", 2);
    attributes->addAttribute(INITIATIVE, initiative);
    northSideAttributes = new Attributes;
    Attribute* melee = new Attribute("melee", 1);
    Attribute* ranged = new Attribute("ranged", 1);
    northSideAttributes->addAttribute(MELEE, melee);
    northSideAttributes->addAttribute(RANGED, ranged);
    //REVIEW: sideAttributes are local table if i'm correct so they will be wiped out if we leave this scope
    Attributes* sideAttributes[6];
    sideAttributes[NORTH] = northSideAttributes;
    unit = new Unit(HEGEMONY, "UniversalSoldier", attributes, sideAttributes);
  }
  ~UnitTest() {}
  void SetUp() {}
  void TearDown() {}

  Unit* unit;
  Attributes* northSideAttributes;
};

TEST_F(UnitTest, testGetSideAttributes) {
  //REVIEW: this test is not working because you compare two pointers
  ASSERT_EQ(northSideAttributes, unit->getSideAttributes(NORTH));
}
