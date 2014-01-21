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
}

TEST_F(ModelTest, shouldMoveToNextPlayer) {
  Player* first = new Player(MOLOCH);
  Player* second = new Player(OUTPOST);
  model->addPlayer(first);
  model->addPlayer(second);
  ASSERT_EQ(2, model->getPlayersQuantity());
  EXPECT_EQ(first, model->getCurrentPlayer());
  model->moveToNextPlayer();
  EXPECT_EQ(second, model->getCurrentPlayer());
  model->moveToNextPlayer();
  EXPECT_EQ(first, model->getCurrentPlayer());
}
