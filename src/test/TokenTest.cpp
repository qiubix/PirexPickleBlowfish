#include <gmock/gmock.h>
using ::testing::Eq;
#include <gtest/gtest.h>
using ::testing::Test;

#include "logic/BoardToken.hpp"

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
