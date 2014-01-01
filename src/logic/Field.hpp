#ifndef FIELD_HPP
#define FIELD_HPP

#include "Token.hpp"

class Field
//REVIEW: same comment according to sections naming and order as in BoardToken class
{
  Token* token;
public:
  Field();
  Token* getToken();
};

#endif //FIELD_HPP
