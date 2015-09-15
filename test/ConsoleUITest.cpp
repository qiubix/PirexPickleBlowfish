#include <gmock/gmock.h>
using ::testing::Eq;
using ::testing::Test;

#include "../src/logic/Attribute.hpp"
#include "../src/logic/BoardToken.hpp"

TEST(ConsoleUITest, shouldTestNothing) {
  ASSERT_THAT(1, Eq(1));
}
