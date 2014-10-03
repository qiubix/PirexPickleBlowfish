#include "Field.hpp"

Field::Field(void)
  : neighbours({{Side::NORTH, nullptr},{Side::NORTH_EAST, nullptr},{Side::NORTH_WEST, nullptr},
               {Side::SOUTH, nullptr},{Side::SOUTH_EAST, nullptr},{Side::SOUTH_WEST, nullptr}})
{
  token = nullptr;
}

Token* Field::getToken(void) {
  return token;
}

Field* Field::getNeighbour(const Side& side) const
{
  return neighbours.at(side); // throws out_of_range exception, which shouldn't occur in our case
}

void Field::setToken(Token* token)
{
  this -> token = token;
}

void Field::addNeighbour(Field* field, const Side& side)
{
  neighbours[side] = field;
}
