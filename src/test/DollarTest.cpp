#include "src/Dollar.hpp"

#include <gmock/gmock.h>
using ::testing::Eq;
#include <gtest/gtest.h>
using ::testing::Test;

class DollarTest : public Test {
protected:
    DollarTest(){}
    ~DollarTest(){}

    virtual void SetUp(){}
    virtual void TearDown(){}
};

TEST_F(DollarTest, testMultiplication) {
    Dollar* five = new Dollar(5);
    five -> times(2);

    EXPECT_THAT(10, Eq(five->amount));
}


TEST_F(DollarTest, testMultiplication1) {
    Dollar* five = new Dollar(5);
    five -> times(2);

    ASSERT_TRUE(10 == five->amount);
}

TEST_F(DollarTest, testMultiplication2) {
    Dollar* six = new Dollar(6);
    six -> times(2);

    ASSERT_EQ(12, six->amount);
}
