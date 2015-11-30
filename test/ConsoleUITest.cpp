#include <gmock/gmock.h>
using ::testing::Eq;
using ::testing::Test;

#include "../src/logic/Attribute.hpp"
#include "../src/logic/BoardToken.hpp"

TEST(ConsoleUITest, shouldTestNothing) {
  ASSERT_THAT(1, Eq(1));
}


/*
 * should indicate empty board at the beginning
 * should inform player about possible actions
 * should allow to display current state of the board
 * should allow to draw tokens
 * should display current "hand"
 * should allow to put tokens on board
 */

