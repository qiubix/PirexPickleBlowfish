#ifndef FIELD_HPP
#define FIELD_HPP

#include <gtest/gtest.h>

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
  void setNeighbours(Field** neighbours);
private:
  Token* token;
  Field** neighbours;

  FRIEND_TEST(FieldTest, shouldSetToken);
  FRIEND_TEST(FieldTest, shouldAddNeighbour);
};

#endif //FIELD_HPP
