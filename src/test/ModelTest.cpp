#include <gmock/gmock.h>
using ::testing::Eq;
#include <gtest/gtest.h>
using ::testing::Test;

#include "logic/Model.hpp"

class ModelTest : public Test
{
protected:
  ModelTest(void) {
    model = new Model;
  }
  ~ModelTest(void) {
    delete model;
  }
  Model* model;

  virtual void SetUp(void) {}
  virtual void TearDown(void) {}
};

TEST_F(ModelTest, shouldGetGameState) {
  GameState currentState = model->getGameState();
  EXPECT_EQ(PAUSE, currentState);
}

TEST_F(ModelTest, shouldSetGameState) {
  model->setGameState(GAME);
  GameState currentState = model->getGameState();
  EXPECT_EQ(GAME, currentState);
}

TEST_F(ModelTest, shouldGetPlayersQuantity) {
  int quantity = model->getPlayersQuantity();
  EXPECT_EQ(0, quantity);
  Player* player = new Player(MOLOCH);
  model->players.push_back(player);
  quantity = model->getPlayersQuantity();
  EXPECT_EQ(1, quantity);
  model->players.clear();
}

TEST_F(ModelTest, shouldReturnNullForNoPlayers) {
  Player* player = model->getCurrentPlayer();
  EXPECT_EQ(NULL, player);
  int playersQuantity = model->getPlayersQuantity();
  EXPECT_EQ(0, playersQuantity);
}

TEST_F(ModelTest, shouldAddPlayer) {
  Player* player = model->getCurrentPlayer();
  EXPECT_EQ(NULL, player);
  Player* newPlayer = new Player(MOLOCH);
  model->addPlayer(newPlayer);
  player = model->getCurrentPlayer();
  EXPECT_EQ(newPlayer, player);
  int playersQuantity = model->getPlayersQuantity();
  EXPECT_EQ(1, playersQuantity);
  delete player;
}

TEST_F(ModelTest, shouldMoveToNextPlayer) {
  Player* firstPlayer = new Player(MOLOCH);
  Player* secondPlayer = new Player(OUTPOST);
  model->addPlayer(firstPlayer);
  model->addPlayer(secondPlayer);
  ASSERT_EQ(2, model->getPlayersQuantity());
  EXPECT_EQ(firstPlayer, model->getCurrentPlayer());
  model->moveToNextPlayer();
  EXPECT_EQ(secondPlayer, model->getCurrentPlayer());
  model->moveToNextPlayer();
  EXPECT_EQ(firstPlayer, model->getCurrentPlayer());
  delete secondPlayer;
  delete firstPlayer;
}

TEST_F(ModelTest, shouldResetGame) {
  Player* player = new Player(MOLOCH);
  model->addPlayer(player);
  model->setGameState(GAME);
  EXPECT_EQ(1, model->getPlayersQuantity());
  EXPECT_EQ(player, model->getCurrentPlayer());
  EXPECT_EQ(GAME, model->getGameState());
  model->reset();
  EXPECT_EQ(PAUSE, model-> getGameState());
  EXPECT_EQ(0, model->getPlayersQuantity());
  EXPECT_EQ(NULL, model->getCurrentPlayer());
}
