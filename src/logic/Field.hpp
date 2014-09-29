#ifndef FIELD_HPP
#define FIELD_HPP

#include "Token.hpp"
#include "Side.hpp"

class Field
{
public:
  Field(void);
  ~Field(void) {}

  //getters
  Token* getToken(void);
  Field* getNeighbour(Side side);

  void setToken(Token* token);
  void addNeighbour(Field* field, Side side);

private:
  Token* token;
  Field** neighbours;
};

#endif //FIELD_HPP
