#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <vector>
#include <list>
#include <gtest/gtest.h>
#include "BoardToken.hpp"

class Player
{
public:
  Player(Army army);
  ~Player(void) {}

  //getters
  Army getArmy(void);

  void addTokens(std::vector<Token*> tokens);

  void killToken(BoardToken* token);
  void useToken(Token* token);
  void putOnBoard(BoardToken* token);
  void drawTokens(int amount = 3);

private:
  Army army;
  std::vector <Token*> hiddenTokens;
  std::vector <BoardToken*> tokensOnBoard;
  std::list <Token*> tokensOnHand;
  std::vector <Token*> usedTokens;

  FRIEND_TEST(PlayerTest, shouldKillToken);
  FRIEND_TEST(PlayerTest, shouldUseToken);
  FRIEND_TEST(PlayerTest, shouldPutTokenOnBoard);
  FRIEND_TEST(PlayerTest, shouldDrawTokens);
  FRIEND_TEST(ControllerTest, shouldActivateToken);
  FRIEND_TEST(ModelTest, shouldDestroyToken);
};

#endif //PLAYER_HPP
