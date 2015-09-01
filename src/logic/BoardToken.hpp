#ifndef BOARDTOKEN_HPP
#define BOARDTOKEN_HPP

#include "Token.hpp"
#include "Side.hpp"
#include "Field.hpp"
#include "Attributes.hpp"

class BoardToken : public Token
{
public:
  BoardToken(Army army, std::string name, Attributes* attributes = nullptr);
  virtual ~BoardToken();

  void addAttribute(AttributeName name, Attribute* attribute);
  void removeAttribute(AttributeName name);
  void upgradeAttributeBy(AttributeName name, int upgradeValue = 1);
  void downgradeAttributeBy(AttributeName name, int downgradeValue = 1);
  void rotateClockwise();
  void rotateAnticlockwise();

  //getters
  Attribute* getAttribute(AttributeName name);
  Attributes* getAttributes();
  Field *getField();
  Side getOrientation();

  //setters
  void setArmy(Army army);
  void resetArmy();
  void setField(Field* field);
  void setOrientation(Side orientation);

private:
  Field* field;
  Attributes* attributes;
  Side orientation;
};

#endif //BOARDTOKEN_HPP
