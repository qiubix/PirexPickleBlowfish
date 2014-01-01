#include <gmock/gmock.h>
using ::testing::Eq;
#include <gtest/gtest.h>
using ::testing::Test;

#include "src/logic/BoardToken.hpp"

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
