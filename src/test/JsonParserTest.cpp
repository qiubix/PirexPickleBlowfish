#include <gmock/gmock.h>
using ::testing::Eq;
#include <gtest/gtest.h>
using ::testing::Test;
using ::testing::Types;

#include "BoostJson.hpp"

const std::string JSON_FILE_TO_READ = "data.json";

template <typename T>
class jsonTest : public Test {
public:
//  typedef std::list<T> List;
//  static T shared_;
//  T value_;
protected:
  jsonTest() {
  }

  ~jsonTest() {
  }

  virtual void SetUp() {}
  virtual void TearDown() {}
};

typedef Types<BoostJson> jsonTypes;
TYPED_TEST_CASE(jsonTest, jsonTypes);

TYPED_TEST(jsonTest, shouldGetStringValueFromJson) {
  FAIL();
}

TYPED_TEST(jsonTest, shouldGetIntegerValueFromJson) {
  FAIL();
}

TYPED_TEST(jsonTest, shouldGetBoolValueFromJson) {
  FAIL();
}

TYPED_TEST(jsonTest, shouldWriteStringValueToJson) {
  FAIL();
}

TYPED_TEST(jsonTest, shouldWriteIntegerValueToJson) {
  FAIL();
}

TYPED_TEST(jsonTest, shouldWriteBoolValueToJson) {
  FAIL();
}

TYPED_TEST(jsonTest, shouldThrowExceptionIfTypeNotSupported) {
  FAIL();
}

//class JsonParserTest : public Test
//{
//protected:
//  JsonParserTest() {
//    parser = new BoostJsonParser();
//    json.put("something", "string");
//  }

//  ~JsonParserTest() {
//  }

//  virtual void SetUp() {}
//  virtual void TearDown() {}

//  JsonParser* parser;
//  Json json;
//};

//TEST_F(JsonParserTest, parserReadsJsonFromFile) {
//  parser -> readJsonFromFile(JSON_FILE_TO_READ);
//  FAIL();
//}

//TEST_F(JsonParserTest, parserWritesJsonToFile) {
//  FAIL();
//}

//TEST_F(JsonParserTest, parserGetsStringFromJson) {
//  FAIL();
//}

//TEST_F(JsonParserTest, parserGetsIntegerFromJson) {
//  FAIL();
//}

//TEST_F(JsonParserTest, parserGetsArrayFromJson) {
//  FAIL();
//}

//TEST_F(JsonParserTest, parserGetsNodeFromJson) {
//  FAIL();
//}
