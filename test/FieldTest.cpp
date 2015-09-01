#include <gmock/gmock.h>
using ::testing::Eq;
#include <gtest/gtest.h>
using ::testing::Test;

#include "../src/logic/Field.hpp"
#include "../src/logic/BoardToken.hpp"

class FieldTest : public Test
{
protected:
  Field field;
};

TEST_F(FieldTest, shouldSetToken) {
  BoardToken token {Army::MOLOCH, "soldier"};
  field.setToken(&token);
  EXPECT_EQ(&token, field.getToken());
};

TEST_F(FieldTest, shouldGetToken) {
  Token newToken {Army::MOLOCH, "soldier"};
  field.setToken(&newToken);
  Token* token = field.getToken();
  EXPECT_EQ(&newToken, token);
  EXPECT_EQ(newToken.getName(), token->getName());
};

TEST_F(FieldTest, shouldAddNeighbour) {
  Field neighbour;
  field.addNeighbour(&neighbour, Side::NORTH);
  EXPECT_EQ(&neighbour, field.getNeighbour(Side::NORTH));
}

TEST_F(FieldTest, shouldGetNeighbour) {
  Token firstToken {Army::MOLOCH, "first token"};
  Token secondToken {Army::MOLOCH, "second token"};
  Field newNeighbour;
  newNeighbour.setToken(&secondToken);
  field.setToken(&firstToken);
  EXPECT_EQ("first token", field.getToken() -> getName());
  field.addNeighbour(&newNeighbour, Side::NORTH);
  Field* neighbour = field.getNeighbour(Side::SOUTH);
  EXPECT_EQ(nullptr, neighbour);
  neighbour = field.getNeighbour(Side::NORTH);
  ASSERT_EQ(&newNeighbour, neighbour);
  EXPECT_EQ("second token", neighbour->getToken()->getName());
};
