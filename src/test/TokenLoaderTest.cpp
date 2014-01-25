#include <gmock/gmock.h>
using ::testing::Eq;
using ::testing::Return;
#include <gtest/gtest.h>
using ::testing::Test;
using ::testing::_;


#include "setup/Json.hpp"
#include "setup/JsonParser.hpp"
#include "setup/StringToEnumTranslator.hpp"
#include "setup/GameBox.hpp"
#include "setup/TokenLoader.hpp"

#include "MockJson.hpp"

#include <fstream>

const std::string STRING_KEY = "string";
const std::string INTEGER_KEY = "integer";
const std::string BOOLEAN_KEY = "boolean";
const std::string SECOND_BOOLEAN_KEY = "anotherBoolean";
const std::string OBJECT_KEY = "object";
const std::string ARRAY_KEY = "array";
const std::string STRING_ARRAY_KEY = "stringArray";
const std::string INTEGER_ARRAY_KEY = "notPresentKey";
const std::string NOT_PRESENT_KEY = "notPresentKey";

const std::string STRING_VALUE = "stringValue";
const int INTEGER_VALUE = 5;
const bool BOOLEAN_VALUE = true;
const bool SECOND_BOOLEAN_VALUE = false;

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
  EXPECT_EQ(NORTH, side);

  side = StringToEnumTranslator::getInstance() -> getSide("northEast");
  EXPECT_EQ(NORTH_EAST, side);

  side = StringToEnumTranslator::getInstance() -> getSide("southEast");
  EXPECT_EQ(SOUTH_EAST, side);

  side = StringToEnumTranslator::getInstance() -> getSide("south");
  EXPECT_EQ(SOUTH, side);

  side = StringToEnumTranslator::getInstance() -> getSide("southWest");
  EXPECT_EQ(SOUTH_WEST, side);

  side = StringToEnumTranslator::getInstance() -> getSide("northWest");
  EXPECT_EQ(NORTH_WEST, side);
}

class GameBoxTest : public Test {
protected:
  GameBoxTest() {}

  virtual ~GameBoxTest() {}

  virtual void SetUp() {}
  virtual void TearDown() {}

};

//TODO: these tests are somehow betonized, think of changing them
// maybe wrapping some things in a class would help?
//FIXME: handle memory deallocating in all GameBoxTests
TEST_F(GameBoxTest, shouldCreateBoxWithNoArmiesByDefault) {
  GameBox gameBox;
  ASSERT_TRUE(gameBox.armies.empty());
}

TEST_F(GameBoxTest, shouldReturnArmiesCountInTheBox) {
  GameBox gameBox;
  ASSERT_EQ(0, gameBox.getArmiesCount());
  std::vector<Token *> army;
  gameBox.armies.insert(std::make_pair<Army, std::vector<Token *> >(HEGEMONY, army));
  ASSERT_EQ(1, gameBox.getArmiesCount());
}

TEST_F(GameBoxTest, shouldCheckIfThereIsNoArmyInTheBox) {
  GameBox gameBox;
  ASSERT_EQ(0, gameBox.getArmiesCount());
  ASSERT_TRUE(gameBox.isEmpty());
  std::vector<Token *> army;
  gameBox.armies.insert(std::make_pair<Army, std::vector<Token *> >(HEGEMONY, army));
  ASSERT_FALSE(gameBox.isEmpty());
}

TEST_F(GameBoxTest, shouldGetArmyFromTheBox) {
  GameBox gameBox;

  //TODO: wrap in into a method
  Army armyName = HEGEMONY;
  std::string tokenName = "someToken";
  Attributes attributes;
  Token* tokenToInsert = new BoardToken(armyName, tokenName, &attributes);
  std::vector<Token*> army;
  army.push_back(tokenToInsert);

  gameBox.armies.insert(std::make_pair<Army, std::vector<Token *> >(armyName, army));
  std::vector<Token *> returnedArmy = gameBox.getArmy(armyName);
  ASSERT_EQ(army.size(), returnedArmy.size());
  ASSERT_EQ(armyName, returnedArmy[0] -> getArmy());
  ASSERT_TRUE(dynamic_cast<BoardToken *>(returnedArmy[0]));
  ASSERT_EQ(&attributes, dynamic_cast<BoardToken *>(returnedArmy[0]) -> getAttributes());
  ASSERT_EQ(tokenName, dynamic_cast<BoardToken *>(returnedArmy[0]) -> getName());
}

TEST_F(GameBoxTest, shouldThrowExceptionWhenNoSuchArmyInTheBox) {
  ASSERT_TRUE(GameBox::getInstance() -> isEmpty());
  ASSERT_THROW(GameBox::getInstance() -> getArmy(OUTPOST), NoSuchArmyInBoxException);
  ASSERT_TRUE(GameBox::getInstance() -> isEmpty());
}

TEST_F(GameBoxTest, shouldAddArmyToTheBox) {
  GameBox gameBox;

  //TODO: wrap in into a method
  Army armyName = HEGEMONY;
  std::string tokenName = "someToken";
  Attributes attributes;
  Token* tokenToInsert = new BoardToken(armyName, tokenName, &attributes);
  std::vector<Token*> army;
  army.push_back(tokenToInsert);

  gameBox.addArmy(armyName, army);
  ASSERT_EQ(1, gameBox.getArmiesCount());

  std::vector<Token*> returnedArmy = gameBox.getArmy(armyName);
  ASSERT_EQ(army.size(), returnedArmy.size());
  ASSERT_EQ(armyName, returnedArmy[0] -> getArmy());
  ASSERT_TRUE(dynamic_cast<BoardToken *>(returnedArmy[0]));
  ASSERT_EQ(&attributes, dynamic_cast<BoardToken *>(returnedArmy[0]) -> getAttributes());
  ASSERT_EQ(tokenName, dynamic_cast<BoardToken *>(returnedArmy[0]) -> getName());
}

TEST_F(GameBoxTest, shouldAddTokenToTheArmy) {
  GameBox gameBox;
  Army armyName = HEGEMONY;
  std::vector<Token*> army;
  gameBox.addArmy(armyName, army);
  std::vector<Token*> returnedArmy = gameBox.getArmy(armyName);
  ASSERT_EQ(0, returnedArmy.size());

  std::string tokenName = "someToken";
  Attributes attributes;
  Token* tokenToInsert = new BoardToken(armyName, tokenName, &attributes);
  gameBox.addTokenToArmy(armyName, tokenToInsert);
  returnedArmy = gameBox.getArmy(armyName);
  ASSERT_EQ(1, returnedArmy.size());

  //TODO: these three assertions are used in some tests, wrap them into a method but first read the googletest documentation
  ASSERT_TRUE(dynamic_cast<BoardToken *>(returnedArmy[0]));
  ASSERT_EQ(&attributes, dynamic_cast<BoardToken *>(returnedArmy[0]) -> getAttributes());
  ASSERT_EQ(tokenName, dynamic_cast<BoardToken *>(returnedArmy[0]) -> getName());
}

TEST_F(GameBoxTest, shouldThrowExceptionWhenTryingToAddTokenOfArmyThatIsNotInTheBox) {
  GameBox gameBox;
  Army armyName = HEGEMONY;
  std::string tokenName = "someToken";
  Attributes attributes;
  Token* tokenToInsert = new BoardToken(armyName, tokenName, &attributes);
  ASSERT_THROW(gameBox.addTokenToArmy(armyName, tokenToInsert), NoSuchArmyInBoxException);
  ASSERT_TRUE(gameBox.isEmpty());
}

TEST_F(GameBoxTest, shouldAddEmptyArmyToTheBox) {
  GameBox gameBox;
  Army armyName = HEGEMONY;
  gameBox.addEmptyArmy(armyName);
  ASSERT_EQ(1, gameBox.getArmiesCount());
  ASSERT_EQ(0, gameBox.getArmy(armyName).size());
}


//TODO: write separate test fixture for modules, units, instants and hqs
class TokenLoaderTest : public Test {
protected:
  TokenLoaderTest() {}

  virtual ~TokenLoaderTest() {}

  virtual void SetUp() {}
  virtual void TearDown() {}

  void createShortJsonFile(std::string fileName, std::string content);
  ModuleToken* createModuleToken(Army army = HEGEMONY);
  UnitToken* createUnitToken(Army army = HEGEMONY);
};

void TokenLoaderTest::createShortJsonFile(std::string fileName, std::string content) {
  std::ofstream jsonFile(fileName.c_str());
  if (jsonFile.is_open()) {
    jsonFile << content;
    jsonFile.close();
  }
}

ModuleToken* TokenLoaderTest::createModuleToken(Army army) {
  std::vector<Side> activeEdges;
  return new ModuleToken(army, "Boss", new Attributes(), activeEdges);
}

UnitToken* TokenLoaderTest::createUnitToken(Army army) {
  Attributes* northSideAttributes = new Attributes();
  northSideAttributes -> addAttribute(MELEE, new Attribute("melee", 1));
  northSideAttributes -> addAttribute(RANGED, new Attribute("ranged", 1));

  Attributes* baseAttributes = new Attributes();
  baseAttributes -> addAttribute(INITIATIVE, new Attribute("initiative", 1));

  UnitToken* unit = new UnitToken(army, "someUnit", baseAttributes);
  unit->setEdgeAttributes(NORTH, northSideAttributes);
  return unit;
}

TEST_F(TokenLoaderTest, shouldLoadTheTestFile) {
  Json* json = JsonParser::getInstance() -> parse("test.json");
  ASSERT_FALSE(json->isEmpty());
}

TEST_F(TokenLoaderTest, shouldLoadModuleAttributes) {
  const std::string ATTRIBUTE = "toughness";
  createShortJsonFile("moduleWithAttribute.json", "{\"attributes\": [{\"name\": \"" + ATTRIBUTE + "\", \"value\":1}]}");
  Json* moduleWithAttribute = JsonParser::getInstance() -> parse("moduleWithAttribute.json");
  Attributes* moduleWithAttributeAttributes = TokenLoader::getInstance() -> loadModuleAtrributes(moduleWithAttribute->getArray("attributes"));
  ASSERT_NE((Attributes*)NULL, moduleWithAttributeAttributes);
  ASSERT_FALSE(moduleWithAttributeAttributes -> empty());
  AttributeName attributeName = StringToEnumTranslator::getInstance() -> getAttributeName(ATTRIBUTE);
  Attribute* moduleAttribute = moduleWithAttributeAttributes -> getAttribute(attributeName);
  ASSERT_EQ(1, moduleAttribute -> getValue());

  createShortJsonFile("moduleWithNoAttribute.json", "{}");
  Json* moduleWithNoAttribute = JsonParser::getInstance() -> parse("moduleWithNoAttribute.json");
  Attributes* moduleWithNoAttributeAttributes = TokenLoader::getInstance() -> loadModuleAtrributes(moduleWithNoAttribute->getArray("attributes"));
  ASSERT_NE((Attributes*)NULL, moduleWithNoAttributeAttributes);
  ASSERT_TRUE(moduleWithNoAttributeAttributes -> empty());
}

TEST_F(TokenLoaderTest, shouldLoadModuleActiveEdges) {
  createShortJsonFile("someActiveEdges.json", "{\"sides\": [\"north\", \"south\"]}");
  Json* someActiveEdges = JsonParser::getInstance() -> parse("someActiveEdges.json");
  std::vector<Side> expectedActiveEdges;
  expectedActiveEdges.push_back(NORTH);
  expectedActiveEdges.push_back(SOUTH);
  std::vector<Side> activeEdges = TokenLoader::getInstance() -> loadModuleActiveEdges(someActiveEdges->getStringArray("sides"));
  ASSERT_EQ(expectedActiveEdges.size(), activeEdges.size());
  for(int currentActiveEdge = 0; currentActiveEdge < expectedActiveEdges.size(); currentActiveEdge++) {
    ASSERT_EQ(expectedActiveEdges[currentActiveEdge], activeEdges[currentActiveEdge]);
  }
}

//FIXME: delete dynamically allocated objects - but first check destructors of Module, ModuleToken, Upgrader and its children
TEST_F(TokenLoaderTest, shouldDecorateModuleWithTwoChangeAttributeUpgrades) {
  Json* upgradesParameters = JsonParser::getInstance() -> parse("twoChangeAttributeUpgradesParameters.json");
  ASSERT_FALSE(upgradesParameters -> isEmpty());

  ModuleToken* moduleToken = createModuleToken();
  Module* module = TokenLoader::getInstance() -> decorateModuleWithUpgrades(moduleToken, upgradesParameters->getArray("upgrades"));
  ASSERT_TRUE(dynamic_cast<Upgrader *>(module));
  ASSERT_FALSE(dynamic_cast<Upgrader *>(module) -> isAffectingEnemies());

  UnitToken* unit = createUnitToken();
  ASSERT_EQ(1, unit -> getAttribute(INITIATIVE) -> getValue());
  ASSERT_EQ(1, unit -> getEdgeAttributes(NORTH) -> getAttribute(MELEE) -> getValue());
  ASSERT_EQ(1, unit -> getEdgeAttributes(NORTH) -> getAttribute(RANGED) -> getValue());

  module -> addBoardToken(unit);
  ASSERT_EQ(3, unit -> getAttribute(INITIATIVE) -> getValue());
  ASSERT_EQ(2, unit -> getEdgeAttributes(NORTH) -> getAttribute(MELEE) -> getValue());
  ASSERT_EQ(1, unit -> getEdgeAttributes(NORTH) -> getAttribute(RANGED) -> getValue());
}

TEST_F(TokenLoaderTest, shouldDecorateModuleWithOneChangeAttributeOfEnemyUpgrade) {
  Json* upgradesParameters = JsonParser::getInstance() -> parse("oneChangeAttributeOfEnemyUpgradeParameters.json");
  ASSERT_FALSE(upgradesParameters -> isEmpty());

  ModuleToken* moduleToken = createModuleToken();
  Module* module = TokenLoader::getInstance() -> decorateModuleWithUpgrades(moduleToken, upgradesParameters->getArray("upgrades"));
  ASSERT_TRUE(dynamic_cast<Upgrader *>(module));
  ASSERT_TRUE(dynamic_cast<Upgrader *>(module) -> isAffectingEnemies());

  UnitToken* unit = createUnitToken(OUTPOST);
  ASSERT_EQ(1, unit -> getAttribute(INITIATIVE) -> getValue());
  ASSERT_EQ(1, unit -> getEdgeAttributes(NORTH) -> getAttribute(MELEE) -> getValue());
  ASSERT_EQ(1, unit -> getEdgeAttributes(NORTH) -> getAttribute(RANGED) -> getValue());

  module -> addBoardToken(unit);
  ASSERT_EQ(0, unit -> getAttribute(INITIATIVE) -> getValue());
  ASSERT_EQ(1, unit -> getEdgeAttributes(NORTH) -> getAttribute(MELEE) -> getValue());
  ASSERT_EQ(1, unit -> getEdgeAttributes(NORTH) -> getAttribute(RANGED) -> getValue());
}

TEST_F(TokenLoaderTest, shouldDecorateModuleWithChangeArmyUpgrade) {
  Json* upgradesParameters = JsonParser::getInstance() -> parse("changeArmyUpgradeParameters.json");
  ASSERT_FALSE(upgradesParameters -> isEmpty());

  ModuleToken* moduleToken = createModuleToken();
  Module* module = TokenLoader::getInstance() -> decorateModuleWithUpgrades(moduleToken, upgradesParameters->getArray("upgrades"));
  ASSERT_TRUE(dynamic_cast<Upgrader *>(module));
  ASSERT_TRUE(dynamic_cast<Upgrader *>(module) -> isAffectingEnemies());

  UnitToken* unit = createUnitToken(OUTPOST);
  ASSERT_EQ(OUTPOST, unit -> getArmy());

  module -> addBoardToken(unit);
  ASSERT_EQ(HEGEMONY, unit -> getArmy());
}

TEST_F(TokenLoaderTest, shouldDecorateModuleWithTwoAddAttributeUpgrades) {
  Json* upgradesParameters = JsonParser::getInstance() -> parse("twoAddAttributeUpgradesParameters.json");
  ASSERT_FALSE(upgradesParameters -> isEmpty());

  ModuleToken* moduleToken = createModuleToken();
  Module* module = TokenLoader::getInstance() -> decorateModuleWithUpgrades(moduleToken, upgradesParameters->getArray("upgrades"));
  ASSERT_TRUE(dynamic_cast<Upgrader *>(module));
  ASSERT_FALSE(dynamic_cast<Upgrader *>(module) -> isAffectingEnemies());

  UnitToken* unit = createUnitToken();
  ASSERT_EQ((Attribute *)NULL, unit -> getAttribute(MOTHER));
  ASSERT_EQ((Attribute *)NULL, unit -> getAttribute(QUARTERMASTER));

  module -> addBoardToken(unit);
  ASSERT_NE((Attribute *)NULL, unit -> getAttribute(MOTHER));
  ASSERT_NE((Attribute *)NULL, unit -> getAttribute(QUARTERMASTER));
}

TEST_F(TokenLoaderTest, shouldDecorateModuleWithOneAddAttributeAndOneChangeAttributeUpgrades) {
  Json* upgradesParameters = JsonParser::getInstance() -> parse("oneAddAttributeAndOneChangeAttributeUpgradesParameters.json");
  ASSERT_FALSE(upgradesParameters -> isEmpty());

  ModuleToken* moduleToken = createModuleToken();
  Module* module = TokenLoader::getInstance() -> decorateModuleWithUpgrades(moduleToken, upgradesParameters->getArray("upgrades"));
  ASSERT_TRUE(dynamic_cast<Upgrader *>(module));
  ASSERT_FALSE(dynamic_cast<Upgrader *>(module) -> isAffectingEnemies());

  UnitToken* unit = createUnitToken();
  ASSERT_EQ(1, unit -> getAttribute(INITIATIVE) -> getValue());
  ASSERT_EQ((Attribute *)NULL, unit -> getAttribute(MOTHER));

  module -> addBoardToken(unit);
  ASSERT_EQ(2, unit -> getAttribute(INITIATIVE) -> getValue());
  ASSERT_NE((Attribute *)NULL, unit -> getAttribute(MOTHER));
}

//TODO: maybe split this test into three tests
//FIXME: add test and funcinallity for multiinitiative
TEST_F(TokenLoaderTest, shouldAddInitiativeLoadedFromJsonToAttributes) {
  std::vector<int> initiativeParameters;
  Attributes* attributes = new Attributes();

  TokenLoader::getInstance() -> loadInitiative(initiativeParameters, attributes);
  ASSERT_TRUE(attributes -> empty());

  initiativeParameters.push_back(1);
  TokenLoader::getInstance() -> loadInitiative(initiativeParameters, attributes);
  ASSERT_EQ(1, attributes -> getSize());
  ASSERT_EQ("initiative", attributes -> getAttribute(INITIATIVE) -> getName());
  ASSERT_EQ(1, attributes -> getAttribute(INITIATIVE) -> getValue());
}

//TODO: again, maybe two separate tests?
TEST_F(TokenLoaderTest, shouldAddMobilityFromJsonToAttributes) {
  Attributes* attributes = new Attributes();

  TokenLoader::getInstance() -> loadMove(false, attributes);
  ASSERT_TRUE(attributes -> empty());

  TokenLoader::getInstance() -> loadMove(true, attributes);
  ASSERT_EQ(1, attributes -> getSize());
  ASSERT_EQ("mobility", attributes -> getAttribute(MOBILITY) -> getName());
  ASSERT_EQ(1, attributes -> getAttribute(MOBILITY) -> getValue());
}

TEST_F(TokenLoaderTest, shouldAddToughnessFromJsonToAttributes) {
  Attributes* attributes = new Attributes();

  TokenLoader::getInstance() -> loadToughness(0, attributes);
  ASSERT_EQ(1, attributes -> getSize());
  ASSERT_EQ("toughness", attributes -> getAttribute(TOUGHNESS) -> getName());
  ASSERT_EQ(1, attributes -> getAttribute(TOUGHNESS) -> getValue());

  attributes -> removeAttribute(TOUGHNESS);
  ASSERT_TRUE(attributes -> empty());

  TokenLoader::getInstance() -> loadToughness(2, attributes);
  ASSERT_EQ(1, attributes -> getSize());
  ASSERT_EQ("toughness", attributes -> getAttribute(TOUGHNESS) -> getName());
  ASSERT_EQ(3, attributes -> getAttribute(TOUGHNESS) -> getValue());
}

//FIXME: REFACTOR: duplication in two tests below
TEST_F(TokenLoaderTest, shouldAddMeleeAttributesToToken) {
  MockJson json;
  std::vector<std::string> keys;
  keys.push_back("north");
  keys.push_back("south");
  keys.push_back("northWest");
  const int NORTH_VALUE = 1;
  const int SOUTH_VALUE = 2;
  const int NORTH_WEST_VALUE = 1;
  ON_CALL(json, getKeys())
    .WillByDefault(Return(keys));
  ON_CALL(json, getIntegerValue(keys[0]))
    .WillByDefault(Return(NORTH_VALUE));
  ON_CALL(json, getIntegerValue(keys[1]))
    .WillByDefault(Return(SOUTH_VALUE));
  ON_CALL(json, getIntegerValue(keys[2]))
    .WillByDefault(Return(NORTH_WEST_VALUE));
  EXPECT_CALL(json, getKeys())
    .Times(1);
  EXPECT_CALL(json, getIntegerValue(_))
    .Times(keys.size());

  Army army = HEGEMONY;
  std::string name = "someName";
  Attributes* attributes = new Attributes();
  UnitToken* token = new UnitToken(army, name, attributes);
  TokenLoader::getInstance() -> loadMelee(token, json);

  ASSERT_EQ(NORTH_VALUE, token -> getEdgeAttributes(NORTH) -> getAttribute(MELEE) -> getValue());
  ASSERT_EQ(SOUTH_VALUE, token -> getEdgeAttributes(SOUTH) -> getAttribute(MELEE) -> getValue());
  ASSERT_EQ(NORTH_WEST_VALUE, token -> getEdgeAttributes(NORTH_WEST) -> getAttribute(MELEE) -> getValue());
}

TEST_F(TokenLoaderTest, shouldAddRangedAttributesToToken) {
  MockJson json;
  std::vector<std::string> keys;
  keys.push_back("north");
  keys.push_back("south");
  keys.push_back("northWest");
  const int NORTH_VALUE = 1;
  const int SOUTH_VALUE = 2;
  const int NORTH_WEST_VALUE = 1;
  ON_CALL(json, getKeys())
    .WillByDefault(Return(keys));
  ON_CALL(json, getIntegerValue(keys[0]))
    .WillByDefault(Return(NORTH_VALUE));
  ON_CALL(json, getIntegerValue(keys[1]))
    .WillByDefault(Return(SOUTH_VALUE));
  ON_CALL(json, getIntegerValue(keys[2]))
    .WillByDefault(Return(NORTH_WEST_VALUE));
  EXPECT_CALL(json, getKeys())
    .Times(1);
  EXPECT_CALL(json, getIntegerValue(_))
    .Times(keys.size());

  Army army = HEGEMONY;
  std::string name = "someName";
  Attributes* attributes = new Attributes();
  UnitToken* token = new UnitToken(army, name, attributes);
  TokenLoader::getInstance() -> loadRanged(token, json);

  ASSERT_EQ(NORTH_VALUE, token -> getEdgeAttributes(NORTH) -> getAttribute(RANGED) -> getValue());
  ASSERT_EQ(SOUTH_VALUE, token -> getEdgeAttributes(SOUTH) -> getAttribute(RANGED) -> getValue());
  ASSERT_EQ(NORTH_WEST_VALUE, token -> getEdgeAttributes(NORTH_WEST) -> getAttribute(RANGED) -> getValue());
}

//FIXME: REFACTOR: duplication in two tests below
TEST_F(TokenLoaderTest, shouldAddShieldAttributesToToken) {
  std::vector<std::string> shieldParameters; //TODO: TESTME: empty vector by default in json.getStringArray
  shieldParameters.push_back("north");
  shieldParameters.push_back("northEast");

  Army army = HEGEMONY;
  std::string name = "someName";
  Attributes* attributes = new Attributes();
  UnitToken* token = new UnitToken(army, name, attributes);

  for(int side = 0; side < 6; side++) {
    ASSERT_EQ(NULL, token -> getEdgeAttributes((Side)side));
  }

  TokenLoader::getInstance() -> loadShield(token, shieldParameters);

  Attribute * northSideShieldAttribute = token -> getEdgeAttributes(NORTH) -> getAttribute(SHIELD);
  ASSERT_NE((Attribute*)NULL, northSideShieldAttribute);
  ASSERT_EQ("shield", northSideShieldAttribute -> getName());
  ASSERT_EQ(1, northSideShieldAttribute -> getValue());

  Attribute * northEastSideShieldAttribute = token -> getEdgeAttributes(NORTH_EAST) -> getAttribute(SHIELD);
  ASSERT_NE((Attribute*)NULL, northEastSideShieldAttribute);
  ASSERT_EQ("shield", northEastSideShieldAttribute -> getName());
  ASSERT_EQ(1, northEastSideShieldAttribute -> getValue());
}

TEST_F(TokenLoaderTest, shouldAddNetAttributesToToken) {
  std::vector<std::string> netParameters; //TODO: TESTME: empty vector by default in json.getStringArray
  netParameters.push_back("north");
  netParameters.push_back("northEast");

  Army army = HEGEMONY;
  std::string name = "someName";
  Attributes* attributes = new Attributes();
  UnitToken* token = new UnitToken(army, name, attributes);

  for(int side = 0; side < 6; side++) {
    ASSERT_EQ(NULL, token -> getEdgeAttributes((Side)side));
  }

  TokenLoader::getInstance() -> loadNet(token, netParameters);

  Attribute * northSideNetAttribute = token -> getEdgeAttributes(NORTH) -> getAttribute(NET);
  ASSERT_NE((Attribute*)NULL, northSideNetAttribute);
  ASSERT_EQ("net", northSideNetAttribute -> getName());
  ASSERT_EQ(1, northSideNetAttribute -> getValue());

  Attribute * northEastSideNetAttribute = token -> getEdgeAttributes(NORTH_EAST) -> getAttribute(NET);
  ASSERT_NE((Attribute*)NULL, northEastSideNetAttribute);
  ASSERT_EQ("net", northEastSideNetAttribute -> getName());
  ASSERT_EQ(1, northEastSideNetAttribute -> getValue());
}
