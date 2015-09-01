#include <gmock/gmock.h>
using ::testing::Eq;
#include <gtest/gtest.h>
using ::testing::Test;

#include <cstdlib>
#include "../src/logic/Attribute.hpp"
#include "../src/logic/BoardToken.hpp"

const int ATTRIBUTE_VALUE = 4;

class BoardTokenTest : public Test
{
protected:
  BoardTokenTest() {
    Attributes* attributes = new Attributes;
    initiative = new Attribute("initiative", ATTRIBUTE_VALUE);
    attributes -> addAttribute(INITIATIVE, initiative);
    token = new BoardToken(HEGEMONY, "test board token", attributes);
  }

  ~BoardTokenTest() {
    delete token;
  }

  BoardToken* token;
  Attribute* initiative;
};

TEST_F(BoardTokenTest, testGetAttribute) {
  Attribute* attribute = token -> getAttribute(INITIATIVE);
  ASSERT_EQ(initiative, attribute);
  ASSERT_EQ(initiative->getName(), attribute->getName());
  ASSERT_EQ(initiative->getValue(), attribute->getValue());
}

TEST_F(BoardTokenTest, testModifyAttribute) {
  token -> upgradeAttributeBy(INITIATIVE);
  ASSERT_EQ(ATTRIBUTE_VALUE + 1, token->getAttribute(INITIATIVE)->getValue());
  token -> downgradeAttributeBy(INITIATIVE);
  ASSERT_EQ(ATTRIBUTE_VALUE, token->getAttribute(INITIATIVE)->getValue());
}

TEST_F(BoardTokenTest, testRemoveAttribute) {
  ASSERT_EQ(1, token -> getAttributes() -> getSize());
  token -> removeAttribute(INITIATIVE);
  ASSERT_EQ(0, token -> getAttributes() -> getSize());
}

TEST_F(BoardTokenTest, testGetOrientation) {
  ASSERT_EQ(Side::NORTH, token->getOrientation());
}

TEST_F(BoardTokenTest, testSetOrientation) {
  token -> setOrientation(Side::SOUTH);
  ASSERT_EQ(Side::SOUTH, token->getOrientation());
}

TEST_F(BoardTokenTest, testRotateClockwise) {
  token -> setOrientation(Side::SOUTH);
  token->rotateClockwise();
  ASSERT_EQ(Side::SOUTH_WEST, token->getOrientation());
}

TEST_F(BoardTokenTest, testRotateAnticlockwise) {
  token -> setOrientation(Side::SOUTH);
  token->rotateAnticlockwise();
  ASSERT_EQ(Side::SOUTH_EAST, token->getOrientation());
}
