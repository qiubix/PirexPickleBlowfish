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

void Player::activateToken(Token* token)
{
  std::vector< Token* >::iterator it = hiddenTokens.begin();
  while (it != hiddenTokens.end()) {
    if(*it == token) {
      hiddenTokens.erase(it);
      break;
    }
    ++it;
  }
  activeTokens.push_back(token);
}

void Player::drawTokens(int amount)
{
  //TODO: implement
}
