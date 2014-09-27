#include <gmock/gmock.h>
using ::testing::Eq;
#include <gtest/gtest.h>
using ::testing::Test;

#include "setup/StringToEnumTranslator.hpp"

class StringToEnumTranslatorTest : public Test {
protected:
  StringToEnumTranslatorTest() {}

  virtual ~StringToEnumTranslatorTest() {}

  virtual void SetUp() {}
  virtual void TearDown() {}
};

//TODO: read about value parametrized tests and maybe use them here
//or just make tables with arguments and expected values and execute this tests in a loop
TEST_F(StringToEnumTranslatorTest, shouldReturnArmy) {
  Army army = StringToEnumTranslator::getInstance() -> getArmy("Moloch");
  EXPECT_EQ(MOLOCH, army);

  army = StringToEnumTranslator::getInstance() -> getArmy("Borgo");
  EXPECT_EQ(BORGO, army);

  army = StringToEnumTranslator::getInstance() -> getArmy("Outpost");
  EXPECT_EQ(OUTPOST, army);

  army = StringToEnumTranslator::getInstance() -> getArmy("Hegemony");
  EXPECT_EQ(HEGEMONY, army);
}

TEST_F(StringToEnumTranslatorTest, shouldReturnAttributeName) {
  AttributeName name = StringToEnumTranslator::getInstance() -> getAttributeName("initiative");
  EXPECT_EQ(INITIATIVE, name);

  name = StringToEnumTranslator::getInstance() -> getAttributeName("toughness");
  EXPECT_EQ(TOUGHNESS, name);

  name = StringToEnumTranslator::getInstance() -> getAttributeName("melee");
  EXPECT_EQ(MELEE, name);

  name = StringToEnumTranslator::getInstance() -> getAttributeName("ranged");
  EXPECT_EQ(RANGED, name);

  name = StringToEnumTranslator::getInstance() -> getAttributeName("shield");
  EXPECT_EQ(SHIELD, name);

  name = StringToEnumTranslator::getInstance() -> getAttributeName("net");
  EXPECT_EQ(NET, name);

  name = StringToEnumTranslator::getInstance() -> getAttributeName("medic");
  EXPECT_EQ(MEDIC, name);

  name = StringToEnumTranslator::getInstance() -> getAttributeName("mother");
  EXPECT_EQ(MOTHER, name);

  name = StringToEnumTranslator::getInstance() -> getAttributeName("mobility");
  EXPECT_EQ(MOBILITY, name);

  name = StringToEnumTranslator::getInstance() -> getAttributeName("quartermaster");
  EXPECT_EQ(QUARTERMASTER, name);
}

TEST_F(StringToEnumTranslatorTest, shouldReturnZeroByDefault) {
  AttributeName name = StringToEnumTranslator::getInstance() -> getAttributeName("notPresentAttribute");
  EXPECT_EQ((AttributeName)0, name);
}

TEST_F(StringToEnumTranslatorTest, shouldReturnSide) {
  Side side = StringToEnumTranslator::getInstance() -> getSide("north");
  EXPECT_EQ(Side::NORTH, side);

  side = StringToEnumTranslator::getInstance() -> getSide("northEast");
  EXPECT_EQ(Side::NORTH_EAST, side);

  side = StringToEnumTranslator::getInstance() -> getSide("southEast");
  EXPECT_EQ(Side::SOUTH_EAST, side);

  side = StringToEnumTranslator::getInstance() -> getSide("south");
  EXPECT_EQ(Side::SOUTH, side);

  side = StringToEnumTranslator::getInstance() -> getSide("southWest");
  EXPECT_EQ(Side::SOUTH_WEST, side);

  side = StringToEnumTranslator::getInstance() -> getSide("northWest");
  EXPECT_EQ(Side::NORTH_WEST, side);
}
