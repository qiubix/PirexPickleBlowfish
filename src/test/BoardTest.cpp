#include <gmock/gmock.h>
using ::testing::Eq;
#include <gtest/gtest.h>
using ::testing::Test;

#include "logic/Board.hpp"
#include "logic/Field.hpp"

class BoardTest : public Test
{
protected:
  BoardTest(void) {
    board = new Board;
  }
  ~BoardTest(void) {
    delete board;
  }

  virtual void SetUp(void) {}
  virtual void TearDown(void) {}

  Board* board;
};

//TODO: check all sides
TEST_F(BoardTest, shouldCreateMiddleRing) {
  Field* middle = board -> getMiddleField();
  Field* northNeighbour = middle -> getNeighbour(NORTH);
  EXPECT_NE((Field*) NULL, northNeighbour);
  EXPECT_EQ(middle, northNeighbour -> getNeighbour(SOUTH));
  Field* southEastNeighbour = middle -> getNeighbour(SOUTH_EAST);
  EXPECT_EQ(middle, southEastNeighbour -> getNeighbour(NORTH_WEST));
  Field* northEastNeighbour = middle -> getNeighbour(NORTH_EAST);
  EXPECT_EQ(northNeighbour, northEastNeighbour -> getNeighbour(NORTH_WEST));
  EXPECT_EQ(northEastNeighbour, northNeighbour -> getNeighbour(SOUTH_EAST));
}
