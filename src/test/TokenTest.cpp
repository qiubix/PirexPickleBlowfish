#include <gmock/gmock.h>
using ::testing::Eq;
#include <gtest/gtest.h>
using ::testing::Test;

#include "src/logic/BoardToken.hpp"

class AttributeTest : public Test
{
protected:
  AttributeTest() {
    attribute = new Attribute("initiative", 2);
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
  ASSERT_EQ(2, attribute->getValue());
}

TEST_F(AttributeTest, testUpgradeAttribute) {
  attribute->upgradeAttribute();
  ASSERT_EQ(3, attribute->getValue());
}

TEST_F(AttributeTest, testDowngradeAttribute) {
  attribute->downgradeAttribute();
  ASSERT_EQ(1, attribute->getValue());
}

class BoardTokenTest : public Test
{
protected:
  BoardTokenTest() {
    Attributes* attributes = new Attributes;
    initiative = new Attribute("initiative", 2);
    attributes->addAttribute(INITIATIVE, initiative);
    token = new BoardToken(attributes);
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
  ASSERT_EQ(3, token->getAttribute(INITIATIVE)->getValue());
  token->downgradeAttribute(INITIATIVE);
  ASSERT_EQ(2, token->getAttribute(INITIATIVE)->getValue());
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
  token->setOrientation(NORTH_WEST);
  token->rotateClockwise();
  ASSERT_EQ(NORTH, token->getOrientation());
}

TEST_F(BoardTokenTest, testRotateAntiClockwise) {
  token->setOrientation(SOUTH);
  token->rotateAntiClockwise();
  ASSERT_EQ(SOUTH_EAST, token->getOrientation());
  token->setOrientation(NORTH);
  token->rotateAntiClockwise();
  ASSERT_EQ(NORTH_WEST, token->getOrientation());
}
