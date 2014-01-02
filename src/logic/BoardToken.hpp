#ifndef BOARDTOKEN_HPP
#define BOARDTOKEN_HPP

#include <map>
#include <string>
#include "Token.hpp"
#include "Field.hpp"
#include "Attributes.hpp"

enum Side {
  NORTH,
  NORTH_EAST,
  SOUTH_EAST,
  SOUTH,
  SOUTH_WEST,
  NORTH_WEST
};

class BoardToken : public Token
{
public:
  BoardToken(Attributes* attributes);
  ~ BoardToken(void);
  Field* getField(void);
  void setField(Field* field);
  Attribute* getAttribute(AttributeName name);
  void addAttribute(Attribute* attribute);
  void upgradeAttribute(AttributeName name);
  void downgradeAttribute(AttributeName name);
  Side getOrientation(void);
  void setOrientation(Side orientation);
  void rotateClockwise(void);
  void rotateAntiClockwise(void);
private:
  Field* field;
  Attributes* attributes;
  Side orientation;
};

#endif //BOARDTOKEN_HPP
