#include <gmock/gmock.h>
using ::testing::Eq;
#include <gtest/gtest.h>
using ::testing::Test;

#include "logic/Controller.hpp"
#include "logic/Model.hpp"
#include "logic/BoardToken.hpp"
#include "setup/TokenLoader.hpp"

//TODO: create mocks
class ControllerTest : public Test
{
protected:
  ControllerTest(void) {
    model = new Model;
    controller = new Controller(model);
  }
  ~ControllerTest(void) {
    delete controller;
    delete model;
  }
  Controller* controller;
  Model* model;

  virtual void SetUp(void) {}
  virtual void TearDown(void) {}

  BoardToken* createBoardTokenWithToughness();
};

BoardToken* ControllerTest::createBoardTokenWithToughness() {
  Attribute* toughness = new Attribute("toughness", 2);
  BoardToken* token = new BoardToken(MOLOCH, "soldier");
  token -> addAttribute(TOUGHNESS, toughness);
  return token;
}

TEST_F(ControllerTest, shouldInitPlayerWithTokens) {
  std::vector<std::string> armyFiles;
  armyFiles.push_back("moloch.json");
  TokenLoader::getInstance() -> loadArmies(armyFiles, controller);
  controller -> initializeNewPlayer(MOLOCH);
  Player* player = model -> getPlayer(MOLOCH);
  int numberOfTokens = player -> hiddenTokens.size();
  ASSERT_EQ(34, numberOfTokens);
  for (int i=0; i<34; ++i) {
    Token* token = player -> hiddenTokens[i];
    EXPECT_EQ(MOLOCH, token -> getArmy());
  }
}

TEST_F(ControllerTest, shouldRotateToken) {
  BoardToken* token = new BoardToken(MOLOCH, "soldier");
  EXPECT_EQ(Side::NORTH, token -> getOrientation());
  controller -> rotateClockwise(token);
  EXPECT_EQ(Side::NORTH_EAST, token -> getOrientation());
  controller -> rotateAnticlockwise(token);
  EXPECT_EQ(Side::NORTH, token -> getOrientation());
  delete token;
}

TEST_F(ControllerTest, shouldPutTokenOnBoard) {
  Field* field = new Field;
  BoardToken* token = new BoardToken(MOLOCH, "solder");
  controller -> putOnBoard(token, field);
  EXPECT_EQ(token, field -> getToken());
  EXPECT_EQ(field, token -> getField());
}

TEST_F(ControllerTest, shouldMoveToken) {
  BoardToken* token = new BoardToken(MOLOCH, "solder");
  Field* field = new Field;
  Field* destination = new Field;
  token -> setField(field);
  field -> setToken(token);
  controller -> move(token, destination);
  EXPECT_EQ(nullptr, field -> getToken());
  EXPECT_EQ(destination, token -> getField());
  EXPECT_EQ(token, destination -> getToken());
}

TEST_F(ControllerTest, shouldStrikeToken) {
  BoardToken* token = createBoardTokenWithToughness();
  controller -> strikeToken(token, 1);
  EXPECT_EQ(1, token -> getAttribute(TOUGHNESS) -> getValue());
}

//TODO: split into separate tests
TEST_F(ControllerTest, shouldBombStrikeAreaOfOneFieldRadius) {
  Field* epicentrum = new Field;
  Field* north = new Field;
  Field* south = new Field;
  Field* farNorth = new Field;
  Field* farSouth = new Field;
  epicentrum -> addNeighbour(north, Side::NORTH);
  epicentrum -> addNeighbour(south, Side::SOUTH);
  BoardToken* firstToken = createBoardTokenWithToughness();
  BoardToken* secondToken = createBoardTokenWithToughness();
  BoardToken* thirdToken = createBoardTokenWithToughness();
  BoardToken* fourthToken = createBoardTokenWithToughness();
  BoardToken* fifthToken = createBoardTokenWithToughness();
  controller -> putOnBoard(firstToken, epicentrum);
  controller -> putOnBoard(secondToken, north);
  controller -> putOnBoard(thirdToken, south);
  controller -> putOnBoard(fourthToken, farNorth);
  controller -> putOnBoard(fifthToken, farSouth);

  controller -> bombStrikeField(epicentrum);
  EXPECT_EQ(1, firstToken -> getAttribute(TOUGHNESS) -> getValue());
  EXPECT_EQ(1, secondToken -> getAttribute(TOUGHNESS) -> getValue());
  EXPECT_EQ(1, thirdToken -> getAttribute(TOUGHNESS) -> getValue());
  EXPECT_EQ(2, fourthToken -> getAttribute(TOUGHNESS) -> getValue());
  EXPECT_EQ(2, fifthToken -> getAttribute(TOUGHNESS) -> getValue());
  delete fifthToken;
  delete fourthToken;
  delete thirdToken;
  delete secondToken;
  delete firstToken;
  delete farSouth;
  delete farNorth;
  delete south;
  delete north;
  delete epicentrum;
}

TEST_F(ControllerTest, shouldResetGame) {
  Player* player = new Player(MOLOCH);
  model -> addPlayer(player);
  controller -> setGameState(GAME);
  EXPECT_EQ(GAME, model -> getGameState());
  EXPECT_FALSE(model -> players.empty());
  controller -> reset();
  EXPECT_EQ(PAUSE, model -> getGameState());
  EXPECT_TRUE(model -> players.empty());
  delete player;
}
