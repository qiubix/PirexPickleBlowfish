#include "Token.hpp"

Token::Token(Army army, std::string name) : army(army), name(name){
}

Army Token::getArmy(void) {
  return army;
}

std::string Token::getName(void) {
  return name;
}
