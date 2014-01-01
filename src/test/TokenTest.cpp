#include <gmock/gmock.h>
using ::testing::Eq;
#include <gtest/gtest.h>
using ::testing::Test;

#include "src/logic/BoardToken.hpp"

class AttributeTest : public Test
{
protected:
  AttributeTest(){}
  ~AttributeTest(){}

  Attribute* attribute;

  virtual void SetUp() {
    attribute = new Attribute("initiative", 2);
  }

  virtual void TearDown() {
    delete attribute;
  }
};

TEST_F(AttributeTest, testGetName) {
  ASSERT_EQ("initiative", attribute->getName());
}

TEST_F(AttributeTest, testGetBaseValue) {
  ASSERT_EQ(2, attribute->getBaseValue());
}

TEST_F(AttributeTest, testGetUpgradedValue) {
  ASSERT_EQ(2, attribute->getUpgradedValue());
}

class BoardTokenTest : public Test
{
protected:
  BoardTokenTest(){}
  ~BoardTokenTest(){}

  BoardToken* token;
  Attribute* initiative;

  virtual void SetUp() {
    std::map <std::string, Attribute*> attributes;
    initiative = new Attribute("initiative", 2);
    attributes.insert(std::make_pair<std::string, Attribute*>(initiative->getName(), initiative));
    token = new BoardToken(attributes);
  }

  virtual void TearDown() {
    delete token;
    delete initiative;
  }
};

TEST_F(BoardTokenTest, testGetAttribute) {
  ASSERT_EQ(initiative, token->getAttribute(initiative->getName()));
}

TEST_F(BoardTokenTest, testAddAttribute) {
  Attribute* toughness = new Attribute("toughness", 1);
  token->addAttribute(toughness);
  ASSERT_EQ(toughness, token->getAttribute(toughness->getName()));
  delete toughness;
}

TEST_F(BoardTokenTest, testGetRotation) {
  ASSERT_EQ(NORTH, token->getRotation());
}
