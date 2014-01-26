#include "Player.hpp"

Player::Player(Army army)
  : army(army) {}

Army Player::getArmy() {
  return army;
}

void Player::killToken(BoardToken* token) {
  std::vector< BoardToken* >::iterator it = tokensOnBoard.begin();
  while (it != tokensOnBoard.end()) {
    if(*it == token) {
      tokensOnBoard.erase(it);
      break;
    }
    ++it;
  }
  usedTokens.push_back(token);
}

void Player::useToken(Token* token) {
  std::list < Token* >::iterator it = tokensOnHand.begin();
  while (it != tokensOnHand.end()) {
    if(*it == token) {
      tokensOnHand.erase(it);
      break;
    }
    ++it;
  }
  usedTokens.push_back(token);
}

void Player::putOnBoard(BoardToken* token) {
  std::list < Token* >::iterator it = tokensOnHand.begin();
  while (it != tokensOnHand.end()) {
    if(*it == token) {
      tokensOnHand.erase(it);
      break;
    }
    ++it;
  }
  tokensOnBoard.push_back(token);
}

void Player::drawTokens(int amount) {
  for (int i=0; i<amount; ++i) {
    Token* token = hiddenTokens.back();
    tokensOnHand.push_back(token);
    hiddenTokens.pop_back();
  }
}
