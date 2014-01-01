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
  Attribute* rotation;
public:
  BoardToken();
  BoardToken(std::map <std::string, Attribute*> attributes);
  Field* getField();
  void setField(Field* field);
  Attribute* getAttribute(std::string name);
  void addAttribute(Attribute* attribute);
  Orientation getRotation();
  void setRotation(Orientation rotation);
};

#endif //BOARDTOKEN_HPP
