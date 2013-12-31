#ifndef FIELD_HPP
#define FIELD_HPP

#include "Token.hpp"

class Field
{
  Token* token;
public:
  Field();
  Token* getToken();
};

#endif //FIELD_HPP
