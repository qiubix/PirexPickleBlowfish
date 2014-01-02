#include "Token.hpp"

Token::Token(void) {

}

Token::Token(std::string name) {
  this->name = name;
}

Army Token::getArmy(void) {
  return army;
}

std::string Token::getName(void) {
  return name;
}
