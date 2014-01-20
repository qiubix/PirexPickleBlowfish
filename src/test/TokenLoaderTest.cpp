#include <gmock/gmock.h>
using ::testing::Eq;
#include <gtest/gtest.h>
using ::testing::Test;

#include "setup/Json.hpp"
#include "setup/JsonParser.hpp"
#include "setup/TokenLoader.hpp"

#include <fstream>

const std::string STRING_KEY = "string";
const std::string INTEGER_KEY = "integer";
const std::string BOOLEAN_KEY = "boolean";
const std::string OBJECT_KEY = "object";
const std::string ARRAY_KEY = "array";

const std::string STRING_VALUE = "stringValue";
const int INTEGER_VALUE = 5;
const bool BOOLEAN_VALUE = true;

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

TEST_F(JsonTest, shouldGetBoolValueFromJson) {
  insertBoolean();
  bool returnedBooleanValue = json -> getBooleanValue(BOOLEAN_KEY);
  ASSERT_EQ(BOOLEAN_VALUE, returnedBooleanValue);
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

const std::string JSON_FILE_TO_READ = "jsonToRead.json";
const int numberOfObjectsInArray = 3;

class JsonParserTest : public Test {
protected:
  JsonParserTest() {
    returnedJson = NULL;
  }

  virtual ~JsonParserTest() {
    if (returnedJson != NULL)
      delete returnedJson;
  }

  virtual void SetUp() {}
  virtual void TearDown() {}

  void prepareJsonFile(std::string fileName);

  Json * returnedJson;
};

//TODO: refactor
void JsonParserTest::prepareJsonFile(std::string fileName) {
  std::ofstream jsonFile(fileName.c_str());

  if (jsonFile.is_open()) {
   jsonFile << "{" << "\n";
   jsonFile << "\"" << STRING_KEY << "\"" << ": " << "\"" << STRING_VALUE << "\"" << "," << "\n";
   jsonFile << "\"" << INTEGER_KEY << "\"" << ": " << INTEGER_VALUE << "," << "\n";
   jsonFile << "\"" << BOOLEAN_KEY << "\"" << ": " << (BOOLEAN_VALUE ? "true" : "false") << "," << "\n";

   jsonFile << "\"" << OBJECT_KEY << "\"" << ": {" << "\n";
   jsonFile << "\"" << STRING_KEY << "\"" << ": " << "\"" << STRING_VALUE << "\"" << "," << "\n";
   jsonFile << "\"" << INTEGER_KEY << "\"" << ": " << INTEGER_VALUE << "," << "\n";
   jsonFile << "\"" << BOOLEAN_KEY << "\"" << ": " << (BOOLEAN_VALUE ? "true" : "false") << "\n";
   jsonFile << "}," << "\n";

   jsonFile << "\"" << ARRAY_KEY << "\"" << ": [" << "\n";
   for(int currentObject = 0; currentObject < numberOfObjectsInArray; currentObject++) {
     jsonFile << "{" << "\n";
     jsonFile << "\"" << STRING_KEY << "\"" << ": " << "\"" << STRING_VALUE << "\"" << "," << "\n";
     jsonFile << "\"" << INTEGER_KEY << "\"" << ": " << INTEGER_VALUE << "," << "\n";
     jsonFile << "\"" << BOOLEAN_KEY << "\"" << ": " << (BOOLEAN_VALUE ? "true" : "false") << "\n";
     jsonFile << "}" << (currentObject == numberOfObjectsInArray - 1 ? "" : ",") << "\n";
   }
   jsonFile << "]" << "\n";

   jsonFile << "}" << "\n";
   jsonFile.close();
 }
}

TEST_F(JsonParserTest, shouldReadJsonFromFile) {
  prepareJsonFile(JSON_FILE_TO_READ);
  returnedJson = JsonParser::getInstance() -> parse(JSON_FILE_TO_READ);

  std::string returnedStringValue = returnedJson -> getStringValue(STRING_KEY);
  EXPECT_EQ(STRING_VALUE, returnedStringValue);

  int returnedIntegerValue = returnedJson -> getIntegerValue(INTEGER_KEY);
  EXPECT_EQ(INTEGER_VALUE, returnedIntegerValue);

  bool returnedBooleanValue = returnedJson -> getBooleanValue(BOOLEAN_KEY);
  EXPECT_EQ(BOOLEAN_VALUE, returnedBooleanValue);

  Json returnedObject = returnedJson -> getObject(OBJECT_KEY);
  EXPECT_EQ(STRING_VALUE, returnedObject.getStringValue(STRING_KEY));
  EXPECT_EQ(INTEGER_VALUE, returnedObject.getIntegerValue(INTEGER_KEY));
  EXPECT_EQ(BOOLEAN_VALUE, returnedObject.getBooleanValue(BOOLEAN_KEY));

  std::vector<Json> returnedArrayOfObjects = returnedJson -> getArray(ARRAY_KEY);
  ASSERT_EQ(numberOfObjectsInArray, returnedArrayOfObjects.size());

  for(int currentObject = 0; currentObject < returnedArrayOfObjects.size(); currentObject++) {
    returnedStringValue = returnedArrayOfObjects[currentObject].getStringValue(STRING_KEY);
    returnedBooleanValue =  returnedArrayOfObjects[currentObject].getBooleanValue(BOOLEAN_KEY);
    returnedIntegerValue =  returnedArrayOfObjects[currentObject].getIntegerValue(INTEGER_KEY);

    EXPECT_EQ(STRING_VALUE, returnedStringValue);
    EXPECT_EQ(INTEGER_VALUE, returnedIntegerValue);
    EXPECT_EQ(BOOLEAN_VALUE, returnedBooleanValue);
  }
}

class TokenLoaderTest : public Test {
protected:
  TokenLoaderTest() {}

  virtual ~TokenLoaderTest() {}

  virtual void SetUp() {}
  virtual void TearDown() {}
};

TEST_F(TokenLoaderTest, shouldReturnArmyFromJson) {
  Army army = TokenLoader::getInstance() -> getArmy("Moloch");
  EXPECT_EQ(MOLOCH, army);

  army = TokenLoader::getInstance() -> getArmy("Borgo");
  EXPECT_EQ(BORGO, army);

  army = TokenLoader::getInstance() -> getArmy("Outpost");
  EXPECT_EQ(OUTPOST, army);

  army = TokenLoader::getInstance() -> getArmy("Hegemony");
  EXPECT_EQ(HEGEMONY, army);
}

TEST_F(TokenLoaderTest, shouldLoadTheTestFile) {
  Json* json = JsonParser::getInstance() -> parse("test.json");
  ASSERT_FALSE(json->isEmpty());
}
