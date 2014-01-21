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
  Token* getActiveToken(std::string name);
  Token* getActiveToken(int position);

  void generateNewTokens(void);
  void drawTokens(int amount = 3);

private:
  Army army;
  std::vector <Token*> hiddenTokens;
  std::vector <Token*> activeTokens;

  FRIEND_TEST(ControllerTest, shouldActivateToken);
};

#endif //PLAYER_HPP
