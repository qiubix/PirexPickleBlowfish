#include <gmock/gmock.h>
using ::testing::Eq;
#include <gtest/gtest.h>
using ::testing::Test;

#include "logic/Controller.hpp"
#include "logic/Model.hpp"
#include "logic/BoardToken.hpp"

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
  BoardToken* token = new BoardToken(MOLOCH, "soldier", new Attributes);
  token -> addAttribute(TOUGHNESS, toughness);
  return token;
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
  Field* field = new Field;
  BoardToken* token = new BoardToken(MOLOCH, "solder", NULL);
  controller->putOnBoard(token, field);
  EXPECT_EQ(token, field->getToken());
  EXPECT_EQ(field, token->getField());
}

TEST_F(ControllerTest, shouldMoveToken) {
  BoardToken* token = new BoardToken(MOLOCH, "solder", NULL);
  Field* field = new Field;
  Field* destination = new Field;
  token->setField(field);
  field->setToken(token);
  controller->move(token, destination);
  EXPECT_EQ(NULL, field->getToken());
  EXPECT_EQ(destination, token->getField());
  EXPECT_EQ(token, destination->getToken());
}

TEST_F(ControllerTest, shouldBombStrikeAreaOfOneFieldRadius) {
  Field* epicentrum = new Field;
  Field* north = new Field;
  Field* south = new Field;
  epicentrum->addNeighbour(north, NORTH);
  epicentrum->addNeighbour(south, SOUTH);
  BoardToken* firstToken = createBoardTokenWithToughness();
  BoardToken* secondToken = createBoardTokenWithToughness();
  BoardToken* thirdToken = createBoardTokenWithToughness();
  controller->putOnBoard(firstToken, epicentrum);
  controller->putOnBoard(secondToken, north);
  controller->putOnBoard(thirdToken, south);

  controller->bombStrikeField(epicentrum);
  EXPECT_EQ(1, firstToken->getAttribute(TOUGHNESS)->getValue());
  EXPECT_EQ(1, secondToken->getAttribute(TOUGHNESS)->getValue());
  EXPECT_EQ(1, thirdToken->getAttribute(TOUGHNESS)->getValue());
  //TODO: check if HQ or tokens outside bomb radius are stricken
  delete thirdToken;
  delete secondToken;
  delete firstToken;
  delete south;
  delete north;
  delete epicentrum;
}

TEST_F(ControllerTest, shouldResetGame) {
  Player* player = new Player(MOLOCH);
  model->addPlayer(player);
  controller->setGameState(GAME);
  EXPECT_EQ(GAME, model->getGameState());
  EXPECT_FALSE(model->players.empty());
  controller->reset();
  EXPECT_EQ(PAUSE, model->getGameState());
  EXPECT_TRUE(model->players.empty());
  delete player;
}
