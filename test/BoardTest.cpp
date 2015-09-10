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
  for (Side side = Side::NORTH; side <= Side::NORTH; ++side) {
    Field *neighbour = middle->getNeighbour(side);
    Side neighbourEdge = !side;
    EXPECT_THAT(middle, Eq(neighbour -> getNeighbour(neighbourEdge)));

    Field *previousInRing = middle -> getNeighbour(decrement(side));
    EXPECT_THAT(previousInRing, Eq(neighbour -> getNeighbour(increment(neighbourEdge))));

    Field *nextInRing = middle -> getNeighbour(increment(side));
    EXPECT_THAT(nextInRing, Eq(neighbour -> getNeighbour(decrement(neighbourEdge))));
  }
}

TEST_F(BoardTest, shouldCreateOutsideRing) {
  for (Side side = Side::NORTH; side <= Side::NORTH; ++side) {
    Field* root = board.getMiddleField()-> getNeighbour(side);
    Field* rootNext = board.getMiddleField()-> getNeighbour(increment(side));
    Field* first = root -> getNeighbour(side);
    Field* second = root -> getNeighbour(increment(side));
    Field* third = rootNext -> getNeighbour(increment(side));
    EXPECT_THAT(root, Eq(first -> getNeighbour(!side)) );
    EXPECT_THAT(root, Eq(second -> getNeighbour(!(increment(side)))) );

    EXPECT_THAT(second, Eq(first -> getNeighbour(!(decrement(side)))) );
    EXPECT_THAT(first, Eq(second -> getNeighbour(decrement(side))) );
    EXPECT_THAT(third, Eq(second -> getNeighbour(!(decrement(side)))) );
    EXPECT_THAT(second, Eq(third -> getNeighbour(decrement(side))) );
  }
}
