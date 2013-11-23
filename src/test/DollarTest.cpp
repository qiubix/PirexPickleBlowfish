#include "src/Dollar.hpp"

#include <gmock/gmock.h>
using ::testing::Eq;
#include <gtest/gtest.h>
using ::testing::Test;

class DollarTest : public Test {
protected:
  DollarTest(){}
  ~DollarTest(){}

  virtual void SetUp() {
    Dollar* five = new Dollar(5);
    five -> times(2);
    Dollar* six = new Dollar(6);
    six -> times(2);
  }
  virtual void TearDown() {
    delete six;
    delete five;
  }
  Dollar* five;
  Dollar* six;
};

// Zwykly test. Nonfatal assertion
TEST(DollarTest, testMultiplication) {
  Dollar* five = new Dollar(5);
  five -> times(2);
  EXPECT_THAT(10, Eq(five->amount));
}

// Test fixture. Używa wspólnych danych z innymi testami, zainicjowanymi
// w SetUp(). Musi się nazywać TEST_F. Fatal assertion
TEST_F(DollarTest, testMultiplication1) {
  ASSERT_TRUE(10 == five->amount);
}

// Test z nonfatal i fatal assertions
TEST_F(DollarTest, testMultiplication2) {
  EXPECT_EQ(12, six->amout);
  ASSERT_EQ(10, five->amount);
}

// Komentarze do wywalenia po przeczytaniu
