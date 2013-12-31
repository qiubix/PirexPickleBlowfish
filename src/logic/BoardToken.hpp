#ifndef BOARDTOKEN_HPP
#define BOARDTOKEN_HPP

#include <map>
#include <string>
#include "Token.hpp"
#include "Field.hpp"
#include "Attribute.hpp"

class BoardToken : public Token
{
  Field* field;
  std::map <std::string, Attribute*> attributes;
public:
  BoardToken();
  Field* getField();
  Attribute* getAttribute(std::string name);
};

#endif //BOARDTOKEN_HPP
