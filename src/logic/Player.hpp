#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <vector>
#include "Token.hpp"

//TODO: implement methods
class Player
{
  Player(void);
  ~Player(void) {}

  //getters
  Token* getActiveToken(std::string name);
  Token* getActiveToken(int position);

  void generateNewTokens(void);
  void drawTokens(int amount = 3);

private:
  std::vector <Token*> hiddenTokens;
  std::vector <Token*> activeTokens;
};
