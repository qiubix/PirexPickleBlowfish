#include "Player.hpp"
#include <algorithm>

Player::Player(Army army)
  : army(army) {}

Army Player::getArmy() {
  return army;
}

Token* Player::getTokenOnHand(int position) {
  if (position > 2) {
    return nullptr;
  }
  else {
    return tokensOnHand[position];
  }
}

void Player::addTokens(std::vector<Token*> tokens) {
  this -> hiddenTokens = tokens;
}

void Player::shuffleTokens() {
  std::random_shuffle(hiddenTokens.begin(), hiddenTokens.end());
}

void Player::killToken(BoardToken* token) {
  auto it = tokensOnBoard.begin();
  while (it != tokensOnBoard.end()) {
    if (*it == token) {
      tokensOnBoard.erase(it);
      break;
    }
    ++it;
  }
  usedTokens.push_back(token);
}

void Player::useToken(Token* token) {
  auto it = tokensOnHand.begin();
  while (it != tokensOnHand.end()) {
    if (*it == token) {
      tokensOnHand.erase(it);
      break;
    }
    ++it;
  }
  usedTokens.push_back(token);
}

void Player::putOnBoard(BoardToken* token) {
  auto it = tokensOnHand.begin();
  while (it != tokensOnHand.end()) {
    if (*it == token) {
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
