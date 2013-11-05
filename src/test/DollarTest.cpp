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

    Dollar* five;
};

TEST_F(DollarTest, testMultiplication) {
    five = new Dollar(5);
    five->times(2);

    EXPECT_THAT(10, Eq(five->amount));
}
