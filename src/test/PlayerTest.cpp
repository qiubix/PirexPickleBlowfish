#include <gmock/gmock.h>
using ::testing::Eq;
#include <gtest/gtest.h>
using ::testing::Test;

#include "logic/Player.hpp"
#include "logic/BoardToken.hpp"

class PlayerTest : public Test
{
protected:
  PlayerTest(void) {
    player = new Player(MOLOCH);
  }
  ~PlayerTest(void) {
    delete player;
  }

  virtual void SetUp(void) {}
  virtual void TearDown(void) {}

  Player* player;
};

TEST_F(PlayerTest, shouldGetArmy) {
  EXPECT_EQ(MOLOCH, player->getArmy());
}

TEST_F(PlayerTest, shouldGetActiveToken) {
  Token* token = new Token(MOLOCH, "token");
  player->activeTokens.push_back(token);
  ASSERT_FALSE(player->activeTokens.empty());
  EXPECT_EQ(token, player->getActiveToken("token"));
  EXPECT_EQ(token, player->getActiveToken(0));
}

TEST_F(PlayerTest, shouldActivateToken) {
  Token* hiddenToken = new Token(MOLOCH, "hidden token");
  player->hiddenTokens.push_back(hiddenToken);
  BoardToken* boardToken = new BoardToken(MOLOCH, "board token", NULL);
  ASSERT_FALSE(player->hiddenTokens.empty());
  EXPECT_TRUE(player->activeTokens.empty());
  player->activateToken(hiddenToken);
  EXPECT_TRUE(player->hiddenTokens.empty());
  EXPECT_EQ(1, player->activeTokens.size());
  EXPECT_EQ(hiddenToken, player->activeTokens[0]);
  player->activateToken(boardToken);
  EXPECT_EQ(2, player->activeTokens.size());
  EXPECT_EQ(boardToken, player->activeTokens[1]);
}

TEST_F(PlayerTest, shouldDeactivateToken) {
  Token* token = new Token(MOLOCH, "token");
  BoardToken* boardToken = new BoardToken(MOLOCH, "board token", NULL);
  player->activeTokens.push_back(token);
  player->activeTokens.push_back(boardToken);
  EXPECT_EQ(2, player->activeTokens.size());
  player->deactivateToken(token);
  EXPECT_EQ(1, player->activeTokens.size());
  player->deactivateToken(boardToken);
  EXPECT_EQ(0, player->activeTokens.size());
}
