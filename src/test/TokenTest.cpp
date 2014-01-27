#include <gmock/gmock.h>
using ::testing::Eq;
#include <gtest/gtest.h>
using ::testing::Test;

#include <cstdlib>

#include "logic/Attribute.hpp"
#include "logic/Attributes.hpp"


const int ATTRIBUTE_VALUE = 4;

class AttributeTest : public Test
{
protected:
  AttributeTest() {
    attribute = new Attribute("initiative", ATTRIBUTE_VALUE);
  }
  ~AttributeTest() {
    delete attribute;
  }

  Attribute* attribute;

  virtual void SetUp() {}
  virtual void TearDown() {}
};

TEST_F(AttributeTest, testGetAttributeValues) {
  ASSERT_EQ("initiative", attribute -> getName());
  ASSERT_EQ(ATTRIBUTE_VALUE, attribute -> getValue());
}

TEST_F(AttributeTest, testUpgradeAttribute) {
  attribute -> upgradeBy();
  int upgradedValue = ATTRIBUTE_VALUE + 1;
  ASSERT_EQ(upgradedValue, attribute -> getValue());
  attribute -> upgradeBy(2);
  upgradedValue += 2;
  ASSERT_EQ(upgradedValue, attribute -> getValue());
  attribute -> upgradeTo(ATTRIBUTE_VALUE);
  ASSERT_EQ(ATTRIBUTE_VALUE, attribute -> getValue());
}

TEST_F(AttributeTest, testDowngradeAttribute) {
  attribute -> downgradeBy();
  int downgradedValue = ATTRIBUTE_VALUE - 1;
  ASSERT_EQ(downgradedValue, attribute -> getValue());
  attribute -> downgradeBy(2);
  downgradedValue -= 2;
  ASSERT_EQ(downgradedValue, attribute -> getValue());
  downgradedValue = ATTRIBUTE_VALUE - 1;
  attribute -> downgradeTo(ATTRIBUTE_VALUE-1);
  ASSERT_EQ(downgradedValue, attribute -> getValue());
}

TEST_F(AttributeTest, testResetAttributeValue) {
  attribute -> upgradeTo(ATTRIBUTE_VALUE + 3);
  int value = ATTRIBUTE_VALUE + 3;
  ASSERT_EQ(value, attribute -> getValue());
  attribute -> resetValue();
  value = ATTRIBUTE_VALUE;
  ASSERT_EQ(value, attribute -> getValue());
  attribute -> downgradeTo(ATTRIBUTE_VALUE-1);
  value = ATTRIBUTE_VALUE - 1;
  ASSERT_EQ(value, attribute -> getValue());
  attribute -> resetValue();
  value = ATTRIBUTE_VALUE;
  ASSERT_EQ(value, attribute -> getValue());
}

class AttributesTest : public Test
{
protected:
  AttributesTest() {
  }
  ~AttributesTest() {
  }

  virtual void SetUp() {}
  virtual void TearDown() {}
};

TEST_F(AttributesTest, shouldCreateAttributesObjectWithNoAttributes) {
  Attributes* attributes = new Attributes();
  ASSERT_NE((Attributes *)NULL, attributes);
  ASSERT_TRUE(attributes -> empty());
}

//TODO: test adding and removing attribute

