#ifndef BOARDTOKEN_HPP
#define BOARDTOKEN_HPP

#include <map>
#include <string>
#include "Token.hpp"
#include "Field.hpp"
#include "Attribute.hpp"

enum Orientation {
  NORTH,
  NORTH_EAST,
  SOUTH_EAST,
  SOUTH,
  SOUTH_WEST,
  NORTH_WEST
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
  void upgradeAttribute(std::string name, int newValue);
  Orientation getRotation();
  void setRotation(Orientation rotation);
  void rotateClockwise();
  void rotateAntiClockwise();
};

#endif //BOARDTOKEN_HPP
