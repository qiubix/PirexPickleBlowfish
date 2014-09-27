#include "Field.hpp"

Field::Field(void) {
  token = nullptr;
  neighbours = new Field*[6];
  for (int i=0; i<6; ++i) {
    neighbours[i] = nullptr;
  }
}

Token* Field::getToken(void) {
  return token;
}

Field* Field::getNeighbour(Side side)
{
  return neighbours[static_cast<int>(side)];
}

void Field::setToken(Token* token)
{
  this -> token = token;
}

void Field::addNeighbour(Field* field, Side side)
{
  neighbours[static_cast<int>(side)] = field;
}
