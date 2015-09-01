#include "Field.hpp"

Token * Field::getToken() {
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
