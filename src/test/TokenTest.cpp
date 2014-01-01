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

//REVIEW: wouldn't it be better to make one test from these three tests?
//and also getBaseValue is doubtedly needed at all as i wrote before
TEST_F(AttributeTest, testGetName) {
  ASSERT_EQ("initiative", attribute->getName());
}

TEST_F(AttributeTest, testGetBaseValue) {
  ASSERT_EQ(2, attribute->getBaseValue());
}

TEST_F(AttributeTest, testGetUpgradedValue) {
  ASSERT_EQ(2, attribute->getUpgradedValue());
}

//REVIEW: change this test after applying review comment from Attribute .hpp file
TEST_F(AttributeTest, testUpgradeAttribute) {
  attribute->upgradeAttribute(3);
  ASSERT_EQ(3, attribute->getUpgradedValue());
}

class BoardTokenTest : public Test
{
protected:
  BoardTokenTest(){}
  ~BoardTokenTest(){}

  BoardToken* token;
  //REVIEW: for now it should be just in testGetAttribute because we use it only there
  Attribute* initiative;

  //REVIEW: this setUp method is fired before each test in that testCase, but here we initialize initiative which,
  //as i mentioned above, is used only in one test for now, so it should be done in it
  //REVIEW: i'm not sure that i remember correctly but order of running test case is:
  //constructor
  //each_test (setUp, test, tearDown)
  //destructor
  //so maybe initializing token is good to be done in contstructor
  virtual void SetUp() {
    std::map <std::string, Attribute*> attributes;
    initiative = new Attribute("initiative", 2);
    //REVIEW: this insert looks like shit (because of its length) so it is another reason to wrap attributes map in Attributes class
    //REVIEW: if you added addAttribute method (i wonder if it is necessary as i wrtoe there) you should also wipe this insert
    attributes.insert(std::make_pair<std::string, Attribute*>(initiative->getName(), initiative));
    token = new BoardToken(attributes);
  }

  virtual void TearDown() {
    delete token;
    delete initiative;
  }
};

//REVIEW: this assert is really long, maybe initiating variable like: std::string attributeName
//and Attribute* attribute would make it easier to read
//REVIEW: test looks fine, we can add asserts to check fields values (e.g. aserrt_eq(initiative->getValue(), attribute->getValue())
//i'm not sure what else we can test here
TEST_F(BoardTokenTest, testGetAttribute) {
  ASSERT_EQ(initiative, token->getAttribute(initiative->getName()));
}

//REVIEW: if we decide to keep addAttribute method it should be tested first and used in other tests
TEST_F(BoardTokenTest, testAddAttribute) {
  Attribute* toughness = new Attribute("toughness", 1);
  token->addAttribute(toughness);
  ASSERT_EQ(toughness, token->getAttribute(toughness->getName()));
  delete toughness;
}

TEST_F(BoardTokenTest, testUpgradeAttribute) {
  token->upgradeAttribute("initiative", 3);
  ASSERT_EQ(3, token->getAttribute("initiative")->getUpgradedValue());
}

TEST_F(BoardTokenTest, testGetRotation) {
  ASSERT_EQ(NORTH, token->getRotation());
}

TEST_F(BoardTokenTest, testSetRotation) {
  token->setRotation(SOUTH);
  ASSERT_EQ(SOUTH, token->getRotation());
}

TEST_F(BoardTokenTest, testRotateClockwise) {
  token->setRotation(SOUTH);
  token->rotateClockwise();
  ASSERT_EQ(SOUTH_WEST, token->getRotation());
  token->setRotation(NORTH_WEST);
  token->rotateClockwise();
  ASSERT_EQ(NORTH, token->getRotation());
}

TEST_F(BoardTokenTest, testRotateAntiClockwise) {
  token->setRotation(SOUTH);
  token->rotateAntiClockwise();
  ASSERT_EQ(SOUTH_EAST, token->getRotation());
  token->setRotation(NORTH);
  token->rotateAntiClockwise();
  ASSERT_EQ(NORTH_WEST, token->getRotation());
}
