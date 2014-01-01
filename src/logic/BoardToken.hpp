#ifndef BOARDTOKEN_HPP
#define BOARDTOKEN_HPP

#include <map>
#include <string>
#include "Token.hpp"
#include "Field.hpp"
#include "Attribute.hpp"

enum Orientation {
  NORTH,
  NORTH_WEST,
  SOUTH_WEST,
  SOUTH,
  SOUTH_EAST,
  NORTH_EAST
};

class BoardToken : public Token
{
  Field* field;
  std::map <std::string, Attribute*> attributes;
public:
  BoardToken();
  BoardToken(std::map <std::string, Attribute*> attributes);
  Field* getField();
  Attribute* getAttribute(std::string name);
};

#endif //BOARDTOKEN_HPP
