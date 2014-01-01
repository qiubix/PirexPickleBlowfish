#include <gmock/gmock.h>
using ::testing::Eq;
#include <gtest/gtest.h>
using ::testing::Test;

#include "src/logic/BoardToken.hpp"

class TokenTest : public Test
{
protected:
  TokenTest(){}
  ~TokenTest(){}

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
  }
};

TEST_F(TokenTest, testGetAttribute) {
  ASSERT_EQ(initiative, token->getAttribute(initiative->getName()));
}
