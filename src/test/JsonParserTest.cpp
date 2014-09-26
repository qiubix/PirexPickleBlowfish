#include <gmock/gmock.h>
using ::testing::Eq;
#include <gtest/gtest.h>
using ::testing::Test;

#include "setup/JsonParser.hpp"
#include "JsonConstants.hpp"

#include <fstream>

class JsonParserTest : public Test {
protected:
  JsonParserTest() {
    returnedJson = nullptr;
  }

  virtual ~JsonParserTest() {
    if (returnedJson != nullptr)
      delete returnedJson;
  }

  virtual void SetUp() {}
  virtual void TearDown() {}

  void prepareJsonFile(std::string fileName);

  Json * returnedJson;
};

//TODO: refactor - maybe split into tests like: should read integer from file and so on
//TODO: add reading array of integers, array of strings
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
