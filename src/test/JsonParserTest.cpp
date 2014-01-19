#include <gmock/gmock.h>
using ::testing::Eq;
using ::testing::Return;
#include <gtest/gtest.h>
using ::testing::Test;
using ::testing::Types;

#include "BoostJson.hpp"
#include "BoostJsonParser.hpp"
#include "MockBoostJson.hpp"

#include "QtJson.hpp"
#include "QtJsonParser.hpp"
#include "MockQtJson.hpp"

#include <fstream> //ifstream, ofstream

const std::string STRING_KEY = "string";
const std::string INTEGER_KEY = "integer";
const std::string BOOLEAN_KEY = "boolean";

const std::string STRING_VALUE = "stringValue";
const int INTEGER_VALUE = 5;
const bool BOOLEAN_VALUE = true;

const std::string STRING_KEY_WRITE = "stringWrite";
const std::string INTEGER_KEY_WRITE  = "integerWrite";
const std::string BOOLEAN_KEY_WRITE  = "booleanWrite";

template <class T>
T* CreateJson(void);

template <>
BoostJson* CreateJson<BoostJson>(void) {
  BoostJson* json = new BoostJson();
  json->put(STRING_KEY, STRING_VALUE);
  json->put(INTEGER_KEY, INTEGER_VALUE);
  json->put(BOOLEAN_KEY, BOOLEAN_VALUE);
  return json;
}

template <>
QtJson* CreateJson<QtJson>(void) {
  QtJson* json = new QtJson();
  json->insert(QString::fromStdString(STRING_KEY), QString::fromStdString(STRING_VALUE));
  json->insert(QString::fromStdString(INTEGER_KEY), INTEGER_VALUE);
  json->insert(QString::fromStdString(BOOLEAN_KEY), BOOLEAN_VALUE);
  return json;
}

template <typename T>
class JsonTest : public Test {
protected:
  JsonTest() {
    json = CreateJson<T>();
  }

  virtual ~JsonTest() {
    delete json;
  }

  virtual void SetUp() {}
  virtual void TearDown() {}

  T* json;
};

TYPED_TEST_CASE_P(JsonTest);

TYPED_TEST_P(JsonTest, shouldGetStringValueFromJson) {
  TypeParam* json = this -> json;
  std::string returnedStringValue = json -> getStringValue(STRING_KEY);
  ASSERT_EQ(STRING_VALUE, returnedStringValue);
}

TYPED_TEST_P(JsonTest, shouldGetIntegerValueFromJson) {
  TypeParam* json = this -> json;
  int returnedIntegerValue = json -> getIntegerValue(INTEGER_KEY);
  ASSERT_EQ(INTEGER_VALUE, returnedIntegerValue);
}

TYPED_TEST_P(JsonTest, shouldGetBoolValueFromJson) {
  TypeParam* json = this -> json;
  bool returnedBooleanValue = json -> getBooleanValue(BOOLEAN_KEY);
  ASSERT_EQ(BOOLEAN_VALUE, returnedBooleanValue);
}

TYPED_TEST_P(JsonTest, shouldWriteStringValueToJson) {
  TypeParam* json = this -> json;
  json -> addStringValue(STRING_KEY_WRITE, STRING_VALUE);
  std::string returnedStringValue = json -> getStringValue(STRING_KEY_WRITE);
  ASSERT_EQ(STRING_VALUE, returnedStringValue);
}

TYPED_TEST_P(JsonTest, shouldWriteIntegerValueToJson) {
  TypeParam* json = this -> json;
  json -> addIntegerValue(INTEGER_KEY_WRITE, INTEGER_VALUE);
  int returnedIntegerValue = json -> getIntegerValue(INTEGER_KEY_WRITE);
  ASSERT_EQ(INTEGER_VALUE, returnedIntegerValue);
}

TYPED_TEST_P(JsonTest, shouldWriteBoolValueToJson) {
  TypeParam* json = this -> json;
  json -> addBooleanValue(BOOLEAN_KEY_WRITE, BOOLEAN_VALUE);
  bool returnedBooleanValue = json -> getBooleanValue(BOOLEAN_KEY_WRITE);
  ASSERT_EQ(BOOLEAN_VALUE, returnedBooleanValue);
}

REGISTER_TYPED_TEST_CASE_P(
  JsonTest,
  shouldGetStringValueFromJson,
  shouldGetIntegerValueFromJson,
  shouldGetBoolValueFromJson,
  shouldWriteStringValueToJson,
  shouldWriteIntegerValueToJson,
  shouldWriteBoolValueToJson
);

typedef Types<BoostJson, QtJson> JsonImplementations;
INSTANTIATE_TYPED_TEST_CASE_P(JsonImplementationsTest, JsonTest, JsonImplementations);

const std::string JSON_FILE_TO_READ = "jsonToRead.json";

template <class T>
T* CreateJsonParser(void);

template <>
BoostJsonParser* CreateJsonParser<BoostJsonParser>(void) {
  BoostJsonParser* jsonParser = new BoostJsonParser();
  return jsonParser;
}

template <>
QtJsonParser* CreateJsonParser<QtJsonParser>(void) {
  QtJsonParser* jsonParser = new QtJsonParser();
  return jsonParser;
}

template <class T>
T* CreateMockJson(void);

template <>
MockBoostJson* CreateMockJson<MockBoostJson>(void) {
  MockBoostJson* mockJson = new MockBoostJson();
  return mockJson;
}

template <>
MockQtJson* CreateMockJson<MockQtJson>(void) {
  MockQtJson* mockJson = new MockQtJson();
  return mockJson;
}

//TODO: figure out how initialize just once all objects necessary in testcase (apply to all other testcases)
template <typename T>
class JsonParserTest : public Test {
protected:
  JsonParserTest() {
    jsonParser = CreateJsonParser<typename T::ParserType>();
    mockJson = CreateMockJson<typename T::MockJson>();
  }

  virtual ~JsonParserTest() {
    delete jsonParser;
  }

  virtual void SetUp() {}
  virtual void TearDown() {}

  void prepareJsonFile(std::string fileName);

  typename T::ParserType * jsonParser;
  typename T::MockJson * mockJson;
};

template<typename T>
void JsonParserTest<T>::prepareJsonFile(std::string fileName) {
  std::ofstream jsonFile(fileName.c_str());
  if (jsonFile.is_open()) {
   jsonFile << "{" << "\n";
   jsonFile << "\"" << STRING_KEY_WRITE << "\"" << ": " << "\"" << STRING_VALUE << "\"" << "," << "\n";
   jsonFile << "\"" << INTEGER_KEY_WRITE << "\"" << ": " << INTEGER_VALUE << "," << "\n";
   jsonFile << "\"" << BOOLEAN_KEY_WRITE << "\"" << ": " << (BOOLEAN_VALUE ? "true" : "false") << "\n";
   jsonFile << "}" << "\n";
   jsonFile.close();
 }
}

TYPED_TEST_CASE_P(JsonParserTest);

TYPED_TEST_P(JsonParserTest, shouldGetStringFromJson) {
  typename TypeParam::MockJson * mockJson = this -> mockJson;
  ON_CALL(*mockJson, getStringValue(STRING_KEY))
    .WillByDefault(Return(STRING_VALUE));
  EXPECT_CALL(*mockJson, getStringValue(STRING_KEY))
    .Times(1);

  typename TypeParam::ParserType parser(mockJson);
  std::string returnedStringValue = parser.getStringValue(STRING_KEY);
  ASSERT_EQ(STRING_VALUE, returnedStringValue);
}

TYPED_TEST_P(JsonParserTest, shouldGetIntegerFromJson) {
  typename TypeParam::MockJson * mockJson = this -> mockJson;
  ON_CALL(*mockJson, getIntegerValue(INTEGER_KEY))
    .WillByDefault(Return(INTEGER_VALUE));
  EXPECT_CALL(*mockJson, getIntegerValue(INTEGER_KEY))
    .Times(1);

  typename TypeParam::ParserType parser(mockJson);;
  int returnedIntegerValue = parser.getIntegerValue(INTEGER_KEY);
  ASSERT_EQ(INTEGER_VALUE, returnedIntegerValue);
}

TYPED_TEST_P(JsonParserTest, shouldGetBooleanFromJson) {
  typename TypeParam::MockJson * mockJson = this -> mockJson;
  ON_CALL(*mockJson, getBooleanValue(BOOLEAN_KEY))
    .WillByDefault(Return(BOOLEAN_VALUE));
  EXPECT_CALL(*mockJson, getBooleanValue(BOOLEAN_KEY))
    .Times(1);

  typename TypeParam::ParserType parser(mockJson);;
  int returnedBooleanValue = parser.getBooleanValue(BOOLEAN_KEY);
  ASSERT_EQ(BOOLEAN_VALUE, returnedBooleanValue);
}

TYPED_TEST_P(JsonParserTest, shouldReadJsonFromFile) {
  this -> prepareJsonFile(JSON_FILE_TO_READ);
  typename TypeParam::ParserType * parser = this -> jsonParser;
  parser -> readJsonFromFile(JSON_FILE_TO_READ);
  std::string returnedStringValue = parser -> getStringValue(STRING_KEY_WRITE);
  int returnedIntegerValue = parser -> getIntegerValue(INTEGER_KEY_WRITE);
  bool returnedBooleanValue = parser -> getBooleanValue(BOOLEAN_KEY_WRITE);
  EXPECT_EQ(STRING_VALUE, returnedStringValue);
  EXPECT_EQ(INTEGER_VALUE, returnedIntegerValue);
  EXPECT_EQ(BOOLEAN_VALUE, returnedBooleanValue);
}

REGISTER_TYPED_TEST_CASE_P(
  JsonParserTest,
  shouldGetStringFromJson,
  shouldGetIntegerFromJson,
  shouldGetBooleanFromJson,
  shouldReadJsonFromFile
);

struct BoostJsonParserWithMockedBoostJson {
  typedef BoostJsonParser ParserType;
  typedef MockBoostJson MockJson;
};

struct QtJsonParserWithMockedQtJson {
  typedef QtJsonParser ParserType;
  typedef MockQtJson MockJson;
};

typedef Types<BoostJsonParserWithMockedBoostJson, QtJsonParserWithMockedQtJson> JsonParserImplementations;
INSTANTIATE_TYPED_TEST_CASE_P(JsonParserImplementationTest, JsonParserTest, JsonParserImplementations);
