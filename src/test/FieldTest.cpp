#include <gmock/gmock.h>
using ::testing::Eq;
#include <gtest/gtest.h>
using ::testing::Test;

#include "logic/Field.hpp"
#include "logic/BoardToken.hpp"

class FieldTest : public Test
{
protected:
  FieldTest(void) {
    field = new Field;
  }
  ~FieldTest(void) {
    delete field;
  }

  virtual void SetUp(void) {}
  virtual void TearDown(void) {}

  Field* field;
};

TEST_F(FieldTest, shouldSetToken) {
  BoardToken* token = new BoardToken(MOLOCH, "soldier");
  field -> setToken(token);
  EXPECT_EQ(token, field -> token);
  EXPECT_EQ(token -> getName(), field -> token -> getName());
  delete token;
}

TEST_F(FieldTest, shouldGetToken) {
  Token* newToken = new Token(MOLOCH, "soldier");
  field -> setToken(newToken);
  Token* token = field -> getToken();
  EXPECT_EQ(newToken, token);
  EXPECT_EQ(newToken -> getName(), token -> getName());
  delete token;
}

TEST_F(FieldTest, shouldAddNeighbour) {
  Field* neighbour = new Field;
  field -> addNeighbour(neighbour, Side::NORTH);
//  EXPECT_EQ(neighbour, field -> neighbours[Side::NORTH]);
  EXPECT_EQ(neighbour, field -> getNeighbour(Side::NORTH));
  delete neighbour;
}

TEST_F(FieldTest, shouldGetNeighbour) {
  Token* firstToken = new Token(MOLOCH, "first token");
  Token* secondToken = new Token(MOLOCH, "second token");
  Field* newNeighbour = new Field;
  newNeighbour -> setToken(secondToken);
  field -> setToken(firstToken);
  EXPECT_EQ("first token", field -> getToken() -> getName());
  field -> addNeighbour(newNeighbour, Side::NORTH);
  Field* neighbour = field -> getNeighbour(Side::SOUTH);
  EXPECT_EQ(nullptr, neighbour);
  neighbour = field -> getNeighbour(Side::NORTH);
  ASSERT_EQ(newNeighbour, neighbour);
  EXPECT_EQ("second token", neighbour -> getToken() -> getName());
  delete neighbour;
  delete secondToken;
  delete firstToken;
}
