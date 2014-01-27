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
  Side oppositeEdge(int edge) {
    return (Side) ((edge+3)%6);
  }
  Side increment(int edge) {
    return (Side) ((edge+1)%6);
  }
  Side decrement(int edge) {
    if (edge == 0) {
      return (Side) 5;
    }
    return (Side) (edge-1);
  }

  Board* board;
};

TEST_F(BoardTest, shouldCreateMiddleRing) {
  Field* middle = board -> getMiddleField();
  for (int i=0; i<6; ++i) {
    Field* neighbour = middle -> getNeighbour((Side) i);
    Side neighbourEdge = oppositeEdge(i);
    EXPECT_EQ(middle, neighbour -> getNeighbour(neighbourEdge));

    Field* previousInRing = middle -> getNeighbour(decrement(i));
    EXPECT_EQ(previousInRing, neighbour -> getNeighbour(increment(neighbourEdge)) );

    Field* nextInRing = middle -> getNeighbour(increment(i));
    EXPECT_EQ(nextInRing, neighbour -> getNeighbour(decrement(neighbourEdge)) );
  }
}

TEST_F(BoardTest, shouldCreateOutsideRing) {
  for (int i=0; i<6; ++i) {
    Field* root = board -> getMiddleField() -> getNeighbour((Side) i);
    Field* rootNext = board -> getMiddleField() -> getNeighbour(increment(i));
    Field* first = root -> getNeighbour((Side) i);
    Field* second = root -> getNeighbour(increment(i));
    Field* third = rootNext -> getNeighbour(increment(i));
    EXPECT_EQ(root, first -> getNeighbour(oppositeEdge(i)));
    EXPECT_EQ(root, second -> getNeighbour(oppositeEdge(increment(i))));

//    EXPECT_EQ(second, first -> getNeighbour(decrement(i)));
//    EXPECT_EQ(first, second -> getNeighbour(oppositeEdge(decrement(i))));
//    EXPECT_EQ(third, second -> getNeighbour(decrement(decrement(i))));
//    EXPECT_EQ(second, third -> getNeighbour(oppositeEdge(decrement(decrement(i)))));
  }
}
