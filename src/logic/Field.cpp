#include "Field.hpp"

Field::Field(void) {
  token = NULL;
  neighbours = new Field*[6];
  for (int i=0; i<6; ++i) {
    neighbours[i] = NULL;
  }
}

Token* Field::getToken(void) {
  return token;
}

Field* Field::getNeighbour(Side side)
{
  return neighbours[side];
}

void Field::setToken(Token* token)
{
  this->token = token;
}

void Field::addNeighbour(Field* field, Side side)
{
  neighbours[side] = field;
}

