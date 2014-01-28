#include <gmock/gmock.h>
using ::testing::Eq;
#include <gtest/gtest.h>
using ::testing::Test;

#include "setup/GameBox.hpp"

#include "logic/Attributes.hpp"
#include "logic/BoardToken.hpp"

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
