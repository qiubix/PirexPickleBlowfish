#ifndef INSTANTTOKEN_HPP
#define INSTANTTOKEN_HPP

#include "Token.hpp"

class InstantToken : public Token
{
public:
  InstantToken(Army army, std::string name);
  virtual ~InstantToken(void) {}

  virtual void action(void) = 0;
};

#endif //INSTANTTOKEN_HPP
