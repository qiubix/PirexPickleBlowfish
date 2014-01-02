#include <gmock/gmock.h>
using ::testing::Eq;
#include <gtest/gtest.h>
using ::testing::Test;

class JsonParserTest : public Test
{
protected:
  JsonParserTest() {
  }

  ~JsonParserTest() {
  }

  virtual void SetUp() {}
  virtual void TearDown() {}
};

TEST_F(JsonParserTest, parserReadsJsonFromFile) {
  FAIL();
}

TEST_F(JsonParserTest, parserWritesJsonToFile) {
  FAIL();
}

TEST_F(JsonParserTest, parserGetsStringFromJson) {
  FAIL();
}

TEST_F(JsonParserTest, parserGetsIntegerFromJson) {
  FAIL();
}

TEST_F(JsonParserTest, parserGetsArrayFromJson) {
  FAIL();
}

TEST_F(JsonParserTest, parserGetsNodeFromJson) {
  FAIL();
}
