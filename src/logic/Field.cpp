#include "Field.hpp"

Field::Field(void) {
  token = NULL;
}

Token* Field::getToken(void) {
  return token;
}
