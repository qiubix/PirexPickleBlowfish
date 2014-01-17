#ifndef BOARDTOKEN_HPP
#define BOARDTOKEN_HPP

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
  BoardToken(Army army, std::string name, Attributes* attributes);
  virtual ~BoardToken(void);

  void addAttribute(AttributeName name, Attribute* attribute);
  void removeAttribute(AttributeName name);
  void upgradeAttribute(AttributeName name);
  void downgradeAttribute(AttributeName name);
  void rotateClockwise(void);
  void rotateAnticlockwise(void);

  //getters
  Attribute* getAttribute(AttributeName name);
  Attributes* getAttributes();
  Field* getField(void);
  Side getOrientation(void);

  //setters
  void setField(Field* field);
  void setOrientation(Side orientation);

private:
  Field* field;
  Attributes* attributes;
  Side orientation;
};

#endif //BOARDTOKEN_HPP
