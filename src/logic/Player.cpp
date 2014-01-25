#include "Player.hpp"

Player::Player(Army army)
  : army(army) {}

Army Player::getArmy()
{
  return army;
}

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

void Player::deactivateToken(Token* token)
{
  if (activeTokens.empty()) {
    return;
  }
  std::vector< Token* >::iterator it = activeTokens.begin();
  while (it != activeTokens.end()) {
    if(*it == token) {
      activeTokens.erase(it);
      break;
    }
    ++it;
  }
}

void Player::drawTokens(int amount)
{
  //TODO: implement
}
