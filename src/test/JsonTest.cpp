#include <gmock/gmock.h>
using ::testing::Eq;
#include <gtest/gtest.h>
using ::testing::Test;

#include "setup/Json.hpp"
#include "JsonConstants.hpp"

class JsonTest : public Test {
protected:
  JsonTest() {
    json = new Json();
  }

  virtual ~JsonTest() {
    delete json;
  }

  virtual void SetUp() {}
  virtual void TearDown() {}

  void insertString(void);
  void insertInteger(void);
  void insertBoolean(void);
  void insertObject(void);
  QJsonObject prepareObject(void);
  int insertArray(void);
  int insertStringArray(void);
  int insertIntegerArray(void);

  void assertKeyFound(std::vector<std::string> keys, std::string keyToFind);

  Json* json;
};

void JsonTest::insertString(void) {
  json -> insert(QString::fromStdString(STRING_KEY), QString::fromStdString(STRING_VALUE));
}

void JsonTest::insertInteger(void) {
  json -> insert(QString::fromStdString(INTEGER_KEY), INTEGER_VALUE);
}

void JsonTest::insertBoolean(void) {
  json -> insert(QString::fromStdString(BOOLEAN_KEY), BOOLEAN_VALUE);
  json -> insert(QString::fromStdString(SECOND_BOOLEAN_KEY), SECOND_BOOLEAN_VALUE);
}

void JsonTest::insertObject(void) {
  QJsonObject object = prepareObject();
  json -> insert(QString::fromStdString(OBJECT_KEY), object);
}

QJsonObject JsonTest::prepareObject(void) {
  QJsonObject object;
  object.insert(QString::fromStdString(STRING_KEY), QString::fromStdString(STRING_VALUE));
  object.insert(QString::fromStdString(INTEGER_KEY), INTEGER_VALUE);
  object.insert(QString::fromStdString(BOOLEAN_KEY), BOOLEAN_VALUE);
  return object;
}

int JsonTest::insertArray(void) {
  const int numberOfObjectsToInsert = 3;

  QJsonArray array;
  for(int currentObject = 0; currentObject < numberOfObjectsToInsert; currentObject++)
    array.push_back(prepareObject());
  json -> insert(QString::fromStdString(ARRAY_KEY), array);

  return numberOfObjectsToInsert;
}

int JsonTest::insertStringArray(void) {
  const int numberOfStringsToInsert = 3;

  QJsonArray array;
  for(int currentString = 0; currentString < numberOfStringsToInsert; currentString++)
    array.push_back(QJsonValue(QString::fromStdString(STRING_VALUE)));
  json -> insert(QString::fromStdString(STRING_ARRAY_KEY), array);

  return numberOfStringsToInsert;
}

int JsonTest::insertIntegerArray(void) {
  const int numberOfIntegersToInsert = 3;

  QJsonArray array;
  for(int currentInteger = 0; currentInteger < numberOfIntegersToInsert; currentInteger++)
    array.push_back(QJsonValue(INTEGER_VALUE));
  json -> insert(QString::fromStdString(INTEGER_ARRAY_KEY), array);

  return numberOfIntegersToInsert;
}

TEST_F(JsonTest, shouldGetStringValueFromJson) {
  insertString();
  std::string returnedStringValue = json -> getStringValue(STRING_KEY);
  ASSERT_EQ(STRING_VALUE, returnedStringValue);
}

TEST_F(JsonTest, shouldGetIntegerValueFromJson) {
  insertInteger();
  int returnedIntegerValue = json -> getIntegerValue(INTEGER_KEY);
  ASSERT_EQ(INTEGER_VALUE, returnedIntegerValue);
}

TEST_F(JsonTest, shouldReturnZeroByDefaultWhenAskedForIntegerWhenNoSuchKey) {
  bool returnedIntegerValue = json -> getBooleanValue(INTEGER_KEY);
  ASSERT_EQ(0, returnedIntegerValue);
}

TEST_F(JsonTest, shouldGetBooleanValueFromJson) {
  insertBoolean();
  bool returnedBooleanValue = json -> getBooleanValue(BOOLEAN_KEY);
  ASSERT_EQ(BOOLEAN_VALUE, returnedBooleanValue);
}

TEST_F(JsonTest, shouldReturnFalseByDefaultWhenAskedForBooleanWhenNoSuchKey) {
  insertInteger();
  bool returnedBooleanValue = json -> getBooleanValue(BOOLEAN_KEY);
  ASSERT_FALSE(returnedBooleanValue);
}

TEST_F(JsonTest, shouldGetObjectFromJson) {
  insertObject();

  Json returnedObject = json -> getObject(OBJECT_KEY);

  std::string returnedStringValue = returnedObject.getStringValue(STRING_KEY);
  bool returnedBooleanValue = returnedObject.getBooleanValue(BOOLEAN_KEY);
  int returnedIntegerValue = returnedObject.getIntegerValue(INTEGER_KEY);

  EXPECT_EQ(STRING_VALUE, returnedStringValue);
  EXPECT_EQ(INTEGER_VALUE, returnedIntegerValue);
  EXPECT_EQ(BOOLEAN_VALUE, returnedBooleanValue);
}

TEST_F(JsonTest, shouldGetArrayOfObjectsFromJson) {
  int numberOfObjectsInArray = insertArray();

  std::vector<Json> returnedArrayOfObjects = json -> getArray(ARRAY_KEY);
  ASSERT_EQ(numberOfObjectsInArray, returnedArrayOfObjects.size());

  std::string returnedStringValue;
  bool returnedBooleanValue;
  int returnedIntegerValue;

  for(int currentObject = 0; currentObject < returnedArrayOfObjects.size(); currentObject++) {
    returnedStringValue = returnedArrayOfObjects[currentObject].getStringValue(STRING_KEY);
    returnedBooleanValue =  returnedArrayOfObjects[currentObject].getBooleanValue(BOOLEAN_KEY);
    returnedIntegerValue =  returnedArrayOfObjects[currentObject].getIntegerValue(INTEGER_KEY);

    EXPECT_EQ(STRING_VALUE, returnedStringValue);
    EXPECT_EQ(INTEGER_VALUE, returnedIntegerValue);
    EXPECT_EQ(BOOLEAN_VALUE, returnedBooleanValue);
  }
}

TEST_F(JsonTest, shouldGetArrayOfStringsFromJson) {
  int numberOfStringsInArray = insertStringArray();

  std::vector<std::string> returnedArrayOfStrings = json -> getStringArray(STRING_ARRAY_KEY);
  ASSERT_EQ(numberOfStringsInArray, returnedArrayOfStrings.size());

  std::string returnedStringValue;

  for(int currentString = 0; currentString < returnedArrayOfStrings.size(); currentString++) {
    returnedStringValue = returnedArrayOfStrings[currentString];
    EXPECT_EQ(STRING_VALUE, returnedStringValue);
  }
}

TEST_F(JsonTest, shouldGetArrayOfIntegersFromJson) {
  int numberOfIntegersInArray = insertIntegerArray();

  std::vector<int> returnedArrayOfIntegers = json -> getIntegerArray(INTEGER_ARRAY_KEY);
  ASSERT_EQ(numberOfIntegersInArray, returnedArrayOfIntegers.size());

  int returnedIntegerValue;

  for(int currentInteger = 0; currentInteger < returnedArrayOfIntegers.size(); currentInteger++) {
    returnedIntegerValue = returnedArrayOfIntegers[currentInteger];
    EXPECT_EQ(INTEGER_VALUE, returnedIntegerValue);
  }
}

TEST_F(JsonTest, shouldReturnEmptyArrayOfIntegersByDefaultWhenNoSuchKey) {
  ASSERT_EQ(0, json -> getIntegerArray(INTEGER_ARRAY_KEY).size());
}

TEST_F(JsonTest, shouldReturnIfKeyPresentInJson) {
  insertString();
  EXPECT_TRUE(json -> contains(STRING_KEY));
  EXPECT_FALSE(json -> contains(NOT_PRESENT_KEY));
}

TEST_F(JsonTest, shouldReturnAllKeysFromJson) {
  insertString();
  insertInteger();
  insertObject();
  const int EXPECTED_KEYS_COUNT = 3;
  std::vector<std::string> keysFromJson = json -> getKeys();
  ASSERT_EQ(EXPECTED_KEYS_COUNT, keysFromJson.size());
  ASSERT_NO_FATAL_FAILURE(assertKeyFound(keysFromJson, STRING_KEY));
  ASSERT_NO_FATAL_FAILURE(assertKeyFound(keysFromJson, INTEGER_KEY));
  ASSERT_NO_FATAL_FAILURE(assertKeyFound(keysFromJson, OBJECT_KEY));
}

void JsonTest::assertKeyFound(std::vector<std::string> keys, std::string keyToFind) {
  bool keyFound = false;
  for(int key = 0; key < keys.size(); key++) {
    if(keys[key] == keyToFind) {
      keyFound = true;
      break;
    }
  }
  ASSERT_TRUE(keyFound);
}
