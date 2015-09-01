#include <gmock/gmock.h>
using ::testing::Eq;
#include <gtest/gtest.h>
using ::testing::Test;

#include "../src/logic/Board.hpp"
#include "../src/logic/Field.hpp"

class BoardTest : public Test
{
protected:
  Side increment(Side edge) {
    return ++edge;
  }
  Side decrement(Side edge) {
    return --edge;
  }

  Board board;
};

TEST_F(BoardTest, shouldCreateMiddleRing) {
  Field* middle = board.getMiddleField();
  //REVIEW: what is wrong with for(Side side = Side::NORTH; side <= Side::whatever; side++)
  //TODO: override operator <= for Side to enable for loop usage
  Side side = Side::NORTH;
  do {
    Field* neighbour = middle -> getNeighbour(side);
    Side neighbourEdge = !side;
    EXPECT_EQ(middle, neighbour -> getNeighbour(neighbourEdge));

    Field* previousInRing = middle -> getNeighbour(decrement(side));
    EXPECT_EQ(previousInRing, neighbour -> getNeighbour(increment(neighbourEdge)) );

    Field* nextInRing = middle -> getNeighbour(increment(side));
    EXPECT_EQ(nextInRing, neighbour -> getNeighbour(decrement(neighbourEdge)) );
    ++side;
  } while (side != Side::NORTH);
}

TEST_F(BoardTest, shouldCreateOutsideRing) {
  Side side = Side::NORTH;
  do {
    Field* root = board.getMiddleField()-> getNeighbour(side);
    Field* rootNext = board.getMiddleField()-> getNeighbour(increment(side));
    Field* first = root -> getNeighbour(side);
    Field* second = root -> getNeighbour(increment(side));
    Field* third = rootNext -> getNeighbour(increment(side));
    EXPECT_EQ(root, first -> getNeighbour(!side) );
    EXPECT_EQ(root, second -> getNeighbour(!(increment(side))) );

    EXPECT_EQ(second, first -> getNeighbour(!(decrement(side))) );
    EXPECT_EQ(first, second -> getNeighbour(decrement(side)) );
    EXPECT_EQ(third, second -> getNeighbour(!(decrement(side))) );
    EXPECT_EQ(second, third -> getNeighbour(decrement(side)) );
    ++side;
  } while (side != Side::NORTH);
}
