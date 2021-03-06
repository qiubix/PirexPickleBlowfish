#include <gmock/gmock.h>
using ::testing::Eq;
#include <gtest/gtest.h>
using ::testing::Test;

#include <cstdlib>
#include "logic/Attributes.hpp"
#include "logic/UnitToken.hpp"

class UnitTokenTest : public Test
{
protected:
  UnitTokenTest() {
    northSideAttributes = new Attributes;
    Attribute* melee = new Attribute("melee", 1);
    northSideAttributes -> addAttribute(MELEE, melee);
    baseUnitAttributes = new Attributes;
    unit = new UnitToken(HEGEMONY, "UniversalSoldier", baseUnitAttributes);
    unit -> setEdgeAttributes(NORTH, northSideAttributes);
  }
  ~UnitTokenTest() {}
  void SetUp() {}
  void TearDown() {}

  UnitToken* unit;
  Attributes* baseUnitAttributes;
  Attributes* northSideAttributes;
};

TEST_F(UnitTokenTest, testGetSideAttributes) {
  Attributes* attributes = unit -> getEdgeAttributes(NORTH);
  Attribute* melee = northSideAttributes -> getAttribute(MELEE);
  ASSERT_EQ(northSideAttributes, attributes);
  ASSERT_EQ(melee, attributes -> getAttribute(MELEE));
  ASSERT_EQ(melee -> getValue(), attributes -> getAttribute(MELEE) -> getValue());
}
