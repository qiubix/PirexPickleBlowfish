#include "Player.hpp"

Player::Player(Army army)
  : army(army) {}

Token* Player::getActiveToken(std::string name)
{
  for (unsigned i=0; i<activeTokens.size(); ++i ) {
    if (activeTokens[i]->getName() == name) {
      return activeTokens[i];
    }
  }
  return NULL;
}

Token* Player::getActiveToken(int position)
{
  return activeTokens[position];
}

void Player::generateNewTokens()
{
  //TODO: implement
}

void Player::drawTokens(int amount)
{
  //TODO: implement
}
