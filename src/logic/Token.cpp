#include "Token.hpp"

Token::Token(Army army, std::string name) : name(name){
  this -> army = new Attribute("army", army);
}

Army Token::getArmy() {
  return (Army) army->getValue();
}

std::string Token::getName() {
  return name;
}
