#include <gmock/gmock.h>
using ::testing::Eq;
#include <gtest/gtest.h>
using ::testing::Test;

#include "logic/Controller.hpp"
#include "logic/Model.hpp"
#include "logic/BoardToken.hpp"

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
};

TEST_F(ControllerTest, shouldSetGameState) {
  GameState currentState = model->getGameState();
  EXPECT_EQ(PAUSE, currentState);
  controller->setGameState(GAME);
  currentState = model->getGameState();
  EXPECT_EQ(GAME, currentState);
}

TEST_F(ControllerTest, shouldActivateToken) {
  Player* player = new Player(MOLOCH);
  BoardToken* token = new BoardToken(MOLOCH, "soldier", NULL);
  player->hiddenTokens.push_back(token);
  EXPECT_TRUE(player->activeTokens.empty());
  EXPECT_EQ(1, player->hiddenTokens.size());
  controller->activate(token);
  ASSERT_FALSE(player->activeTokens.empty());
  EXPECT_EQ(token, player->activeTokens[0]);
  EXPECT_EQ("soldier", player->activeTokens[0]->getName());
  delete token;
  delete player;
}

TEST_F(ControllerTest, shouldRotateToken) {
  BoardToken* token = new BoardToken(MOLOCH, "soldier", NULL);
  EXPECT_EQ(NORTH, token->getOrientation());
  controller->rotateClockwise(token);
  EXPECT_EQ(NORTH_EAST, token->getOrientation());
  controller->rotateAnticlockwise(token);
  EXPECT_EQ(NORTH, token->getOrientation());
  delete token;
}

TEST_F(ControllerTest, shouldPutTokenOnBoard) {
  //TODO: test puting token on board
  EXPECT_TRUE(false);
}

TEST_F(ControllerTest, shouldMoveToken) {
  BoardToken* token = new BoardToken(MOLOCH, "solder", NULL);
  Field* field = new Field;
  Field* destination = new Field;
  token->setField(field);
  field->setToken(token);
  ASSERT_EQ(NULL, destination->getToken());
  EXPECT_EQ(field, token->getField());
  EXPECT_EQ(token, field->getToken());
  controller->move(token, destination);
  EXPECT_EQ(NULL, field->getToken());
  EXPECT_EQ(destination, token->getField());
  EXPECT_EQ(token, destination->getToken());
}

TEST_F(ControllerTest, shouldStrikeSurroundingTokens) {
  Field* epicentrum = new Field;
  Field* north = new Field;
  Field* northWest = new Field;
  Field* northEast = new Field;
  Field* south = new Field;
  Field* southEast = new Field;
  Field* southWest = new Field;
  epicentrum->addNeighbour(north, NORTH);
  epicentrum->addNeighbour(northWest, NORTH);
  epicentrum->addNeighbour(northEast, NORTH);
  epicentrum->addNeighbour(south, SOUTH);
  epicentrum->addNeighbour(southWest, SOUTH_WEST);
  epicentrum->addNeighbour(southEast, SOUTH_EAST);
  Attribute* toughness = new Attribute("toughness", 2);
  Attributes* attributes = new Attributes;
  attributes->addAttribute(TOUGHNESS, toughness);
  BoardToken* firstToken = new BoardToken(MOLOCH, "soldier", attributes);
  BoardToken* secondToken = new BoardToken(OUTPOST, "soldier", attributes);
  BoardToken* thirdToken = new BoardToken(HEGEMONY, "soldier", attributes);
  epicentrum->setToken(firstToken);
  north->setToken(secondToken);
  south->setToken(thirdToken);
  EXPECT_EQ(2, firstToken->getAttribute(TOUGHNESS)->getValue());
  EXPECT_EQ(2, secondToken->getAttribute(TOUGHNESS)->getValue());
  EXPECT_EQ(2, thirdToken->getAttribute(TOUGHNESS)->getValue());
  controller->strikeSurroundingTokens(epicentrum);
  EXPECT_EQ(1, firstToken->getAttribute(TOUGHNESS)->getValue());
  EXPECT_EQ(1, secondToken->getAttribute(TOUGHNESS)->getValue());
  EXPECT_EQ(1, thirdToken->getAttribute(TOUGHNESS)->getValue());
  //TODO: check if HQ or tokens outside bomb radius are stricken
}

TEST_F(ControllerTest, shouldResetGame) {
  Player* player = new Player(MOLOCH);
  model->addPlayer(player);
  controller->setGameState(GAME);
  EXPECT_EQ(GAME, model->getGameState());
  EXPECT_FALSE(model->players.empty());
  controller->reset();
  EXPECT_EQ(PAUSE, model->getGameState());
  EXPECT_TRUE(model->usedTokens.empty());
  EXPECT_TRUE(model->players.empty());
  delete player;
}
