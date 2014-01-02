#ifndef FIELD_HPP
#define FIELD_HPP

#include "Token.hpp"

class Field
{
public:
  Field(void);

  //getters
  Token* getToken(void);

private:
  Token* token;
};

#endif //FIELD_HPP
