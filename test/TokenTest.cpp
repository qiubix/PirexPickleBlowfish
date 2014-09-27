#include <gmock/gmock.h>
using ::testing::Eq;
#include <gtest/gtest.h>
using ::testing::Test;

#include <cstdlib>

#include "../src/logic/Attribute.hpp"
#include "../src/logic/Attributes.hpp"

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
  ASSERT_NE(nullptr, attributes);
  ASSERT_TRUE(attributes -> empty());
}

TEST_F(AttributesTest, shouldAddAttribute) {
  Attributes* attributes = new Attributes;
  attributes->addAttribute(INITIATIVE, new Attribute("initiative", 3));
  ASSERT_EQ(1, attributes->getSize());
  ASSERT_EQ(3, attributes->getAttribute(INITIATIVE)->getValue());
}

TEST_F(AttributesTest, shouldRemoveAttribute) {
  Attributes* attributes = new Attributes;
  attributes->addAttribute(INITIATIVE, new Attribute("initiative", 3));
  attributes->removeAttribute(INITIATIVE);
  ASSERT_EQ(0, attributes->getSize());
}

TEST_F(AttributesTest, shouldRemoveAttributeEvenIfItDoesNotExist) {
  Attributes* attributes = new Attributes;
  attributes->removeAttribute(INITIATIVE);
  ASSERT_EQ(0, attributes->getSize());
}
