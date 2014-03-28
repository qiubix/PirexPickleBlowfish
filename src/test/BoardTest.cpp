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
  
	Side oppositeEdge(Side edge) {
		//    return (Side) ((edge+3)%6);
		switch(edge) {
		case Side::NORTH: 
			return Side::SOUTH;
		case Side::NORTH_EAST: 
			return Side::SOUTH_WEST;
		case Side::SOUTH_EAST: 
			return Side::NORTH_WEST;
		case Side::SOUTH: 
			return Side::NORTH;
		case Side::SOUTH_WEST: 
			return Side::NORTH_EAST;
		case Side::NORTH_WEST: 
			return Side::SOUTH_EAST;
		}
  }
  Side increment(Side edge) {
//    return (Side) ((edge+1)%6);
    return ++edge;
  }
  Side decrement(Side edge) {
//    if (edge == 0) {
//      return (Side) 5;
//    }
//    return (Side) (edge-1);
    return --edge;
  }

  Board* board;
};

TEST_F(BoardTest, shouldCreateMiddleRing) {
  Field* middle = board -> getMiddleField();
//  for (int i=0; i<6; ++i) {
//  for (Side side = Side::NORTH; side <= Side::NORTH_WEST; ++side) {
  Side side = Side::NORTH;
  do {
    Field* neighbour = middle -> getNeighbour(side);
    Side neighbourEdge = oppositeEdge(side);
    EXPECT_EQ(middle, neighbour -> getNeighbour(neighbourEdge));

    Field* previousInRing = middle -> getNeighbour(decrement(side));
    EXPECT_EQ(previousInRing, neighbour -> getNeighbour(increment(neighbourEdge)) );

    Field* nextInRing = middle -> getNeighbour(increment(side));
    EXPECT_EQ(nextInRing, neighbour -> getNeighbour(decrement(neighbourEdge)) );
    ++side;
  } while (side != Side::NORTH);
}

TEST_F(BoardTest, shouldCreateOutsideRing) {
//  for (int i=0; i<6; ++i) {
//  for (Side side = Side::NORTH; side <= Side::NORTH_WEST; ++side) {
  Side side = Side::NORTH;
  do {
    Field* root = board -> getMiddleField() -> getNeighbour(side);
    Field* rootNext = board -> getMiddleField() -> getNeighbour(increment(side));
    Field* first = root -> getNeighbour(side);
    Field* second = root -> getNeighbour(increment(side));
    Field* third = rootNext -> getNeighbour(increment(side));
    EXPECT_EQ(root, first -> getNeighbour(oppositeEdge(side)));
    EXPECT_EQ(root, second -> getNeighbour(oppositeEdge(increment(side))));

    EXPECT_EQ(second, first -> getNeighbour(oppositeEdge(decrement(side))));
    EXPECT_EQ(first, second -> getNeighbour(decrement(side)));
    EXPECT_EQ(third, second -> getNeighbour(oppositeEdge(decrement(side))));
    EXPECT_EQ(second, third -> getNeighbour(decrement(side)));
    ++side;
  } while (side != Side::NORTH);
}
