#ifndef FIELD_HPP
#define FIELD_HPP

#include <map>

#include "Token.hpp"
#include "Side.hpp"

class Field
{
public:
  //getters
  Token *getToken();
  Field* getNeighbour(const Side& side);

  void setToken(Token* token);
  void addNeighbour(Field* field, const Side& side);

private:
  Token* token;
  std::map<Side, Field*> neighbours;
};

#endif //FIELD_HPP
