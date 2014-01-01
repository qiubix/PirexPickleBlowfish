#include "src/logic/Dollar.hpp"

#include <gmock/gmock.h>
using ::testing::Eq;
#include <gtest/gtest.h>
using ::testing::Test;

class DollarTest : public Test {
protected:
  DollarTest(){}
  ~DollarTest(){}

  virtual void SetUp() {
    five = new Dollar(5);
    five -> times(2);
    six = new Dollar(6);
    six -> times(2);
  }
  virtual void TearDown() {
    delete six;
    delete five;
  }
  Dollar* five;
  Dollar* six;
};

TEST(DollarNotFixtureTest, testMultiplication) {
  Dollar* five = new Dollar(5);
  five -> times(2);
  EXPECT_THAT(10, Eq(five->amount));
  delete five;
}

TEST_F(DollarTest, testMultiplication1) {
  ASSERT_TRUE(10 == five->amount);
}

TEST_F(DollarTest, testMultiplication2) {
  ASSERT_EQ(12, six->amount);
  ASSERT_EQ(12, five->amount);
}
