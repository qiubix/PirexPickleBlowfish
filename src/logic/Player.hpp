#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <vector>
#include <gtest/gtest.h>
#include "BoardToken.hpp"

class Player
{
public:
  Player(Army army);

  //getters
  Army getArmy();
  Token* getTokenOnHand(int position);

  void addTokens(std::vector<Token*> tokens);
  void shuffleTokens();

  void killToken(BoardToken* token);
  void useToken(Token* token);
  void putOnBoard(BoardToken* token);
  void drawTokens(int amount = 3);

  std::vector <Token*> hiddenTokens;

private:
  Army army;
  std::vector <BoardToken*> tokensOnBoard;
  std::vector <Token*> tokensOnHand;
  std::vector <Token*> usedTokens;

  FRIEND_TEST(PlayerTest, shouldKillToken);
  FRIEND_TEST(PlayerTest, shouldUseToken);
  FRIEND_TEST(PlayerTest, shouldPutTokenOnBoard);
  FRIEND_TEST(PlayerTest, shouldDrawTokens);
  FRIEND_TEST(PlayerTest, shouldGetTokenFromHand);
  FRIEND_TEST(ControllerTest, shouldActivateToken);
  FRIEND_TEST(ModelTest, shouldDestroyToken);
};

#endif //PLAYER_HPP
