#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <vector>
#include <gtest/gtest.h>
#include "Token.hpp"

//TODO: implement methods
class Player
{
public:
  Player(Army army);
  ~Player(void) {}

  //getters
  Army getArmy(void);
  Token* getActiveToken(std::string name);
  Token* getActiveToken(int position);

  void generateNewTokens(void);
  void activateToken(Token* token);
  void deactivateToken(Token* token);
  void drawTokens(int amount = 3);

private:
  Army army;
  std::vector <Token*> hiddenTokens;
  std::vector <Token*> activeTokens;

  FRIEND_TEST(PlayerTest, shouldGetActiveToken);
  FRIEND_TEST(PlayerTest, shouldActivateToken);
  FRIEND_TEST(PlayerTest, shouldDeactivateToken);
  FRIEND_TEST(ControllerTest, shouldActivateToken);
  FRIEND_TEST(ModelTest, shouldDestroyToken);
};

#endif //PLAYER_HPP
