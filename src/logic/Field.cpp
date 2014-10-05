#include "Field.hpp"

Field::Field(void)
{
  token = nullptr;
}

Token* Field::getToken(void) {
  return token;
}

Field* Field::getNeighbour(const Side& side)
{
  return neighbours[side];
}

void Field::setToken(Token* token)
{
  this -> token = token;
}

void Field::addNeighbour(Field* field, const Side& side)
{
  neighbours[side] = field;
}
