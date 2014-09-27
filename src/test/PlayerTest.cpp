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
  }
  ~PlayerTest(void) {
  }

  virtual void SetUp(void) {
    player = new Player(MOLOCH);
  }

  virtual void TearDown(void) {
    delete player;
  }

  Player* player;
};

TEST_F(PlayerTest, shouldKillToken) {
  BoardToken* token = new BoardToken(MOLOCH, "token");
  player -> tokensOnBoard.push_back(token);
  player -> killToken(token);
  EXPECT_TRUE(player -> tokensOnBoard.empty());
  ASSERT_FALSE(player -> usedTokens.empty());
  EXPECT_EQ(token, player -> usedTokens[0]);
  delete token;
}

TEST_F(PlayerTest, shouldUseToken) {
  Token* token = new Token(MOLOCH, "token");
  player -> tokensOnHand.push_back(token);
  player -> useToken(token);
  EXPECT_TRUE(player -> tokensOnHand.empty());
  ASSERT_FALSE(player -> usedTokens.empty());
  EXPECT_EQ(token, player -> usedTokens[0]);
  delete token;
}

TEST_F(PlayerTest, shouldPutTokenOnBoard) {
  BoardToken* token = new BoardToken(MOLOCH, "token");
  player -> tokensOnHand.push_back(token);
  player -> putOnBoard(token);
  EXPECT_TRUE(player -> tokensOnHand.empty());
  ASSERT_FALSE(player -> tokensOnBoard.empty());
  EXPECT_EQ(token, player -> tokensOnBoard[0]);
  delete token;
}

TEST_F(PlayerTest, shouldDrawTokens) {
  Token* token1 = new Token(MOLOCH, "token");
  Token* token2 = new Token(MOLOCH, "token");
  Token* token3 = new Token(MOLOCH, "token");
  Token* token4 = new Token(MOLOCH, "token");
  player -> hiddenTokens.push_back(token1);
  player -> hiddenTokens.push_back(token2);
  player -> hiddenTokens.push_back(token3);
  player -> hiddenTokens.push_back(token4);

  player -> drawTokens(1);
  ASSERT_FALSE(player -> tokensOnHand.empty());
  EXPECT_EQ(token4, player -> tokensOnHand.back());
  EXPECT_EQ(3, player -> hiddenTokens.size());

  player -> drawTokens();
  EXPECT_TRUE(player -> hiddenTokens.empty());
  ASSERT_FALSE(player -> tokensOnHand.empty());
  EXPECT_EQ(token1, player -> tokensOnHand.back());
  EXPECT_EQ(4, player -> tokensOnHand.size());

  delete token1;
  delete token2;
  delete token3;
  delete token4;
}

TEST_F(PlayerTest, shouldGetTokenFromHand) {
  Token* token1 = new Token(MOLOCH, "token");
  Token* token2 = new Token(MOLOCH, "token");
  Token* token3 = new Token(MOLOCH, "token");
  player -> tokensOnHand.push_back(token1);
  player -> tokensOnHand.push_back(token2);
  player -> tokensOnHand.push_back(token3);
  ASSERT_EQ(token1, player -> getTokenOnHand(0));
  ASSERT_EQ(token2, player -> getTokenOnHand(1));
  ASSERT_EQ(token3, player -> getTokenOnHand(2));

  delete token1;
  delete token2;
  delete token3;
}

//TODO: implement
TEST_F(PlayerTest, DISABLED_shouldThrowExceptionWhenGettingNonExistingToken) {
}

//TODO: implement
TEST_F(PlayerTest, DISABLED_shouldThrowExceptionWhenGettingTokenFromWrongPosition) {
}
