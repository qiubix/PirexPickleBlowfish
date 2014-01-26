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

TEST_F(ModelTest, shouldInitializeGameStateWithPause) {
  GameState currentState = model -> getGameState();
  EXPECT_EQ(PAUSE, currentState);
}

TEST_F(ModelTest, shouldInitializeCurrentPlayerIdWithMinusOne) {
  EXPECT_EQ(-1, model -> currentPlayerId);
}

TEST_F(ModelTest, shouldReturnNullForNoPlayers) {
  Player* player = model->getCurrentPlayer();
  EXPECT_EQ(NULL, player);
}

TEST_F(ModelTest, shouldGetPlayersQuantity) {
  Player* player = new Player(MOLOCH);
  model -> players.push_back(player);
  EXPECT_EQ(1, model -> getPlayersQuantity());
  delete player;
}

TEST_F(ModelTest, shouldInitializePlayerQuantityWithZero) {
  int quantity = model -> getPlayersQuantity();
  EXPECT_EQ(0, quantity);
}

TEST_F(ModelTest, shouldAddPlayer) {
  Player* newPlayer = new Player(MOLOCH);
  model -> addPlayer(newPlayer);
  EXPECT_EQ(newPlayer, model -> getCurrentPlayer());
  EXPECT_EQ(1, model -> getPlayersQuantity());
  delete newPlayer;
}

TEST_F(ModelTest, shouldSetCurrentPlayerIdToZeroWhenAddingFirstPlayer) {
  Player* firstPlayer = new Player(MOLOCH);
  Player* secondPlayer = new Player(OUTPOST);
  model -> addPlayer(firstPlayer);
  model -> addPlayer(secondPlayer);
  EXPECT_EQ(0, model -> currentPlayerId);
  delete firstPlayer;
  delete secondPlayer;
}

TEST_F(ModelTest, shouldGetPlayerByArmy) {
  Player* molochPlayer = new Player(MOLOCH);
  Player* outpostPlayer = new Player(OUTPOST);
  model -> addPlayer(molochPlayer);
  model -> addPlayer(outpostPlayer);
  EXPECT_EQ(molochPlayer, model -> getPlayer(MOLOCH));
  delete molochPlayer;
  delete outpostPlayer;
}

TEST_F(ModelTest, shouldMoveToNextPlayer) {
  Player* firstPlayer = new Player(MOLOCH);
  Player* secondPlayer = new Player(OUTPOST);
  model -> addPlayer(firstPlayer);
  model -> addPlayer(secondPlayer);
  EXPECT_EQ(firstPlayer, model -> getCurrentPlayer());
  model -> moveToNextPlayer();
  EXPECT_EQ(secondPlayer, model -> getCurrentPlayer());
  model -> moveToNextPlayer();
  EXPECT_EQ(firstPlayer, model -> getCurrentPlayer());
  delete secondPlayer;
  delete firstPlayer;
}

TEST_F(ModelTest, shouldDestroyToken) {
  Player* player = new Player(MOLOCH);
  model -> addPlayer(player);
  BoardToken* token = new BoardToken(MOLOCH, "token", NULL);
  Field* field = new Field;
  field -> setToken(token);
  token -> setField(field);
  player -> activeTokens.push_back(token);
  model -> killToken(token);
  EXPECT_TRUE(player -> activeTokens.empty());
  ASSERT_EQ(1, model -> usedTokens.size());
  EXPECT_EQ(token, model -> usedTokens[0]);
  EXPECT_EQ(NULL, field -> getToken());
}

TEST_F(ModelTest, shouldResetGame) {
  Player* player = new Player(MOLOCH);
  model -> addPlayer(player);
  model -> setGameState(GAME);
  model -> reset();
  EXPECT_EQ(PAUSE, model -> getGameState());
  EXPECT_EQ(0, model -> getPlayersQuantity());
  EXPECT_EQ(NULL, model -> getCurrentPlayer());
}
